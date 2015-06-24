#Note: not compatible with gcc / ROOT6 on lxplus. Not sure how to solve it. But using ROOT6 the run macro compiles all classes fine
######################

CXX           = g++
LD            = g++

#############################

os = $(shell uname -s)


ifeq ($(os),Linux)
CXXFLAGS      = -I$(ROOTSYS)/include
else
CXXFLAGS      = -O -std=c++11 -fPIC -pipe -Wall -dynamiclib -I$(ROOTSYS)/include
endif

ifeq ($(os),Linux)
LDFLAGS       = -g
LDFLAGSS      = -g -fPIC --shared
else
LDFLAGS       = -O -Xlinker -bind_at_load -flat_namespace
LDFLAGSS      = -dynamiclib -flat_namespace -undefined suppress
LDFLAGSSS     = -bundle
endif

ROOTLIBS      = $(shell root-config --libs)
LIBS          =  $(ROOTLIBS)

HDRS          = hiEvt.h analyzeBJets.h
SRCS          = hiEvt.cc analyzeBJets.cc dictBJets.C

OBJS          = $(SRCS:.C=.o)

PROGRAM       = BJets
SLIB          = libBJets.so

$(PROGRAM):     $(OBJS)
	@echo "Linking $(PROGRAM) for "$(os)
	@echo $(LD) $(LDFLAGSS) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(SLIB)	
	@$(LD) $(LDFLAGSS) $(CXXFLAGS) $(OBJS) $(LIBS) -o $(SLIB)
#@$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o $(PROGRAM)
	@echo "done"

#g++ -g -fPIC --shared hiEvt.cc analyzeBJets.cc dictBJets.o -I/data/alisoft/aliroot/alicore/root/include -L/data/alisoft/aliroot/alicore/root/lib -lCore -lCint -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic -o libBJets.so

##########################################################

BJets.o: BJets.h

dictBJets.C: $(HDRS)
	@echo "Generating dictionary ..."
	@$(ROOTSYS)/bin/rootcint -f dictBJets.C -c $(HDRS)

.C.o:
	$(CXX) $(CXXFLAGS) -c -fPIC $<

clean :
	rm -f *.o dict*.* $(SLIB)
	@echo "All cleaned-up :-)"
