LATEXMK ?= latexmk

LATEXMKOPTS += -pdf -shell-escape

JOBNAME ?= project-report

.PHONY: all clean

all:
	$(LATEXMK) $(LATEXMKOPTS) $(JOBNAME)


clean:
	$(LATEXMK) $(LATEXMKOPTS) -C $(JOBNAME)
