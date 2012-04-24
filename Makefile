BINDIR=bin
INCDIR=include
SRCDIR=src
TESTDIR=test

FLAGS=-ansi
CARDFLAGS=$(FLAGS) -I$(INCDIR)
SIMFLAGS=$(FLAGS) -g -I$(INCDIR) -DSIMULATOR -DTEST

HEADERS=$(wildcard $(INCDIR)/*.h)
SOURCES=$(wildcard $(SRCDIR)/*.c)

SMARTCARD=$(BINDIR)/idemix.smartcard.hzx
SIMULATOR=$(BINDIR)/idemix.simulator.hzx

SOURCES_crypto_compute_hash=$(TESTDIR)/crypto_compute_hash.c $(SRCDIR)/crypto_helper.c $(SRCDIR)/funcs_helper.c
TEST_crypto_compute_hash=$(BINDIR)/crypto_compute_hash.hzx

TEST=$(TEST_crypto_compute_hash)

all: simulator smartcard

$(BINDIR):
	mkdir $(BINDIR)

simulator: $(HEADERS) $(SOURCES) $(SIMULATOR)

$(SIMULATOR): $(HEADERS) $(SOURCES) $(BINDIR)
	hcl $(SIMFLAGS) $(SOURCES) -o $(SIMULATOR)

smartcard: $(HEADERS) $(SOURCES) $(SMARTCARD)

$(SMARTCARD): $(HEADERS) $(SOURCES) $(BINDIR)
	hcl $(CARDFLAGS) $(SOURCES) -o $(SMARTCARD)

test: $(TEST)

$(TEST_crypto_compute_hash): $(HEADERS) $(SOURCES_crypto_compute_hash) $(BINDIR)
	hcl $(SIMFLAGS) $(SOURCES_crypto_compute_hash) -o $(TEST_crypto_compute_hash)

clean:
	rm -rf $(BINDIR)/* $(SRCDIR)/*~ $(INCDIR)/*~ $(TESTDIR)/*~

.PHONY: all clean simulator smartcard test