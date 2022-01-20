# ----------------------------
# Makefile Options
# ----------------------------

NAME ?= VECTCALC
ICON ?= icon.png
DESCRIPTION ?= "Vector Calculator"
COMPRESSED ?= YES
ARCHIVED ?= NO

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk
