
DEV_GUIDE_OUTDIR   ?= dev_guide_html
DEV_GUIDE_SRCDIR   ?= dev_guide_xml
DEV_GUIDE_FILE  ?= $(DEV_GUIDE_SRCDIR)/dev_guide.xml

SRS_OUTDIR ?= srs_html
SRS_SRCDIR ?= srs_xml
SRS_FILE ?= $(SRS_SRCDIR)/srs.xml

PLAN_OUTDIR ?= plan_html
PLAN_SRCDIR ?= plan_xml
PLAN_FILE ?= $(PLAN_SRCDIR)/plan.xml

XSL_FILE  ?= xsl/html.xsl

COMMON_CSS_FILE	 ?= common.css

XSLTPROC ?= xsltproc

help::
	@echo " The Following is a list of supported build targets:"
	@echo
	@echo " dev-guide-html:"
	@echo "     Build HTML version of Developer Guide."
	@echo
	@echo " srs-html:"
	@echo "     Build HTML version of Software Requirements Specification(SRS)."
	@echo
	@echo " plan-html:"
	@echo "     Build HTML version of Project Plan."
	@echo
	@echo " test-dev-guide:"
	@echo "     Validate Developer Guide DocBook XML source."
	@echo
	@echo " test-srs:"
	@echo "     Validate Developer Guide DocBook XML source."
	@echo
	@echo " test-plan:"
	@echo "     Validate Project Plan."
	@echo
	@echo " format:"
	@echo "     Format DocBook XML source using xmlformat."
	@echo
	@echo " clean-dev-guide:"
	@echo "     Remove Manual html files."
	@echo
	@echo " clean-srs-html:"
	@echo "     Remove SRS html files."
	@echo
	@echo " clean-plan-html:"
	@echo "     Remove Project Plan html files."
	@echo
	@echo " clean:"
	@echo "     Remove temporary files."
	@echo

# xsltproc -output option gives I/O errors because??, so 
# just move the html to the output directory
dev-guide-html:: clean-dev-guide-html
	# creating output directory
	-@mkdir $(DEV_GUIDE_OUTDIR)
	# copying entities file to build directory
	-@cp entities.ent $(DEV_GUIDE_SRCDIR)
	# generating html
	LANG=en_US.UTF-8 $(XSLTPROC) -xinclude $(XSL_FILE) $(DEV_GUIDE_FILE)
	# copy html files to output directory
	-@mv *.html $(DEV_GUIDE_OUTDIR)
	# copy css file to output directory
	-@cp css/$(COMMON_CSS_FILE) $(DEV_GUIDE_OUTDIR)/$(COMMON_CSS_FILE)
	# copy the image files to the output directory
	-@cp -r images  $(DEV_GUIDE_OUTDIR)/images

.PHONY : dev-guide-html

srs-html:: clean-srs-html
	# creating output directory
	-@mkdir $(SRS_OUTDIR)
	# copying entities file to build directory
	-@cp entities.ent $(SRS_SRCDIR)
	# generating html
	LANG=en_US.UTF-8 $(XSLTPROC) -xinclude $(XSL_FILE) $(SRS_FILE)
	# copy html files to output directory
	-@mv *.html $(SRS_OUTDIR)
	# copy css file to output directory
	-@cp css/$(COMMON_CSS_FILE) $(SRS_OUTDIR)/$(COMMON_CSS_FILE)
	# copy the image files to the output directory
	-@cp -r images  $(SRS_OUTDIR)/images

.PHONY : srs-html

plan-html:: clean-plan-html
	# creating output directory
	-@mkdir $(PLAN_OUTDIR)
	# copying entities file to build directory
	-@cp entities.ent $(PLAN_SRCDIR)
	# generating html
	LANG=en_US.UTF-8 $(XSLTPROC) -xinclude $(XSL_FILE) $(PLAN_FILE)
	# copy html files to output directory
	-@mv *.html $(PLAN_OUTDIR)
	# copy css file to output directory
	-@cp css/$(COMMON_CSS_FILE) $(PLAN_OUTDIR)/$(COMMON_CSS_FILE)
	# copy the image files to the output directory
	-@cp -r images  $(PLAN_OUTDIR)/images

.PHONY : plan-html

test-dev-guide::
	# validating book
	xmllint --noout --postvalid --xinclude $(DEV_GUIDE_FILE)

.PHONY : test-dev-guide

test-srs::
	# validating book
	xmllint --noout --postvalid --xinclude $(SRS_FILE)

.PHONY : test-srs

test-plan::
	# validating book
	xmllint --noout --postvalid --xinclude $(PLAN_FILE)

.PHONY : test-plan

test:: test-dev-guide test-srs test-plan

.PHONY : test

format:: test
	@for file in `find . -name '*.xml' -type f`; \
		do xmlformat/xmlformat.pl --in-place --backup .bak \
		--config-file xmlformat/xmlformat.conf $$file; \
		done

.PHONY : format

clean-dev-guide-html::
	@rm -rf $(DEV_GUIDE_OUTDIR)

.PHONY : clean-dev-guide-html

clean-srs-html::
	@rm -rf $(SRS_OUTDIR)

.PHONY : clean-srs-html

clean-plan-html::
	@rm -rf $(PLAN_OUTDIR)

.PHONY : clean-srs-html

clean-backup-files::
	@for file in `find . -name '*.bak' -type f`; do \
		rm $$file; done

.PHONY : clean-backup-files

clean:: clean-dev-guide-html clean-srs-html clean-backup-files

.PHONY : clean
