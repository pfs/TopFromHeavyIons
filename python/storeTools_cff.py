import FWCore.ParameterSet.Config as cms
import os,sys
import getopt
import commands
import re

def natural_sort(l):
    convert = lambda text: int(text) if text.isdigit() else text.lower()
    alphanum_key = lambda key: [ convert(c) for c in re.split('([0-9]+)', key) ]
    return sorted(l, key = alphanum_key)

"""
lists the files available in castor
"""
def fillFromStore(directory, mask='', prepend='root://eoscms//eos/cms'):  

    localdataset=cms.untracked.vstring()
    if(len(directory)==0) : return localdataset

    from subprocess import Popen, PIPE
    print 'looking into: '+directory+'...'

    eos_cmd = '/afs/cern.ch/project/eos/installation/0.2.41/bin/eos.select'
    data = Popen([eos_cmd, 'ls', '/eos/cms/'+directory],stdout=PIPE)
    out,err = data.communicate()

    full_list = []

    ## if input file was single root file:
    if directory.endswith('.root'):
        if len(out.split('\n')[0]) > 0:
            return [prepend + directory]

    ## instead of only the file name append the string to open the file in ROOT
    for line in out.split('\n'):
        if len(line.split()) == 0: continue
        full_list.append(prepend + directory + '/' + line)

    ## strip the list of files if required
    if mask != '':
        stripped_list = [x for x in full_list if mask in x]
        return stripped_list

    ## return 
    return full_list


"""
check that a file exist and is not corrupted
"""
def checkInputFile(url):
    if(url.startswith('/store')==True):
       url= 'root://eoscms//eos/cms'+url
    command_out = commands.getstatusoutput("root -l -b -q " + url)
    if(command_out[1].find("Error")>=0 or command_out[1].find("probably not closed")>=0 or command_out[1].find("Corrupted")>=0):return False
    return True


"""
check store for duplicates
"""
def checkStoreForDuplicates(outdir):
    ls_cms = "ls " + outdir
    isEOS=False
    isCastor=False
    if(outdir.find('/store/')==0) :
        isEOS=True
        splitOnString=','
        ls_cms='cmsLs ' + outdir + ' | grep root | awk \'{print $5}\''	
    elif(outdir.find('/store/')==0) :
        isCastor = True
        ls_cms = "rfdir " + outdir + + ' | grep root'
    nOutFile = 0
    lsCmd_out = commands.getstatusoutput(ls_cms)
    jobNumbers = []
    duplicatedJobs = []
    origFiles=[]
    duplicatedFiles=[]
    if lsCmd_out[0] == 0:
        lsCmd_outLines = lsCmd_out[1].split("\n")
        if len(lsCmd_outLines) != 0:
            for fileLine in lsCmd_outLines:
                if not "root" in fileLine: continue
                fileName=fileLine
                if(isCastor) : fileName = fileLine.split()[8]

	        if(checkInputFile(fileName)==True):
		    jobNumber=-1
		    try:
			fileBaseName=os.path.basename(fileName)
			jobNumber=int(fileBaseName.split("_")[1])
		    except:
			continue

		    if jobNumber in jobNumbers:
			if not jobNumber in duplicatedJobs:  duplicatedJobs.append(jobNumber)
			duplicatedFiles.append(fileName)
		    else :
			jobNumbers.append(jobNumber)
			origFiles.append(fileName)
			nOutFile += 1
   	        else:
		    print("   #corrupted file found : " + fileName)
		    duplicatedFiles.append(fileName)
    return natural_sort(duplicatedFiles)


"""
clean up for duplicats in the storage area
"""
def removeDuplicates(dir):
    duplicatedFiles=checkStoreForDuplicates(dir)
    print 'Removing ' + str(len(duplicatedFiles)) + ' duplicated files in ' + dir
    isEOS=False
    isCastor=False
    if(dir.find('/store/')==0) : isEOS=True
    if(dir.find('castor')>=0) : isCastor=True
    for f in duplicatedFiles :
        print f
        if(isEOS) : commands.getstatusoutput('cmsRm ' + f)
        elif(isCastor) : commands.getstatusoutput('rfrm ' +dir + '/' + f)
        else : commands.getstatusoutput('rm ' +dir + '/' + f)

            
"""
wrapper to read the configuration from comand line
args: castor_directory output_file first_file step
"""
def configureSourceFromCommandLine() :
    storeDir=''
    outputFile='Events.root'
    ffile=0
    step=-1
    try:
        if(len(sys.argv)>2 ):
            if(sys.argv[2].find('/')>=0 or sys.argv[2].find('.root')>0) :
                storeDir=sys.argv[2]
                if(len(sys.argv)>3 ):
                    if(sys.argv[3].find('.root')>0):
                        outputFile=sys.argv[3]
                    if(len(sys.argv)>4 ):
                        if(sys.argv[4].isdigit()) : ffile=int(sys.argv[4])
                        if(len(sys.argv)>5 ):
                            if(sys.argv[5].isdigit()) : step=int(sys.argv[5])
    except:
        print '[storeTools_cff] Could not configure from command line, will return default values'

    return outputFile, fillFromStore(storeDir,ffile,step)



def addPrefixSuffixToFileList(Prefix, fileList, Suffix):
   outList = []
   for s in fileList:
      outList.append(Prefix+s+Suffix)
   return natural_sort(outList)

