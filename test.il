// example taken from https://product-help.schneider-electric.com/Machine%20Expert/V1.1/en/SoMProg/SoMProg/FBD_LD_IL_Editor/FBD_LD_IL_Editor-7.htm#XREF_D_SE_0083466_1 for initial testing
//LD      TRUE        load TRUE to accumulator
//ANDN    bVar1       execute AND with negative value of bVar1
//JMPC    m1         if accum. is TRUE, jump to label "m1"
//LDN     bVar2      store negated value of bVar2...
//ST      bRes       ... in bRes
//// test
//
//m1:
//LD      bVar2      store value of bVar2...
//ST      bRes      ... in bRes

LDA 0x100,0x7,0x3,1