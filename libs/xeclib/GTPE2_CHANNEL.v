///////////////////////////////////////////////////////
//  Copyright (c) 1995/2016 Xilinx, Inc.
//  All Right Reserved.
///////////////////////////////////////////////////////
//
//   ____   ___
//  /   /\/   / 
// /___/  \  /     Vendor      : Xilinx 
// \  \    \/      Version : 2016.1
//  \  \           Description : Xilinx Formal Library Component
//  /  /                      
// /__/   /\       Filename    : GTPE2_CHANNEL.v
// \  \  /  \ 
//  \__\/\__ \                    
//                                 
///////////////////////////////////////////////////////
//  Revision:
//  06/02/11 - Initial version
//  09/27/11 - 626008 - YML updated
//  10/24/11 - 630158 - Add message
//  01/04/12 - 640449 - YML update
//  02/01/12 - 641156 - complete GTPE2 wrapper
//  10/31/14 - Added inverter functionality for IS_*_INVERTED parameter (CR 828995).
//  End Revision
/////////////////////////////////////////////////////////

`timescale 1 ps / 1 ps 

`celldefine

module GTPE2_CHANNEL (
  DMONITOROUT,
  DRPDO,
  DRPRDY,
  EYESCANDATAERROR,
  GTPTXN,
  GTPTXP,
  PCSRSVDOUT,
  PHYSTATUS,
  PMARSVDOUT0,
  PMARSVDOUT1,
  RXBUFSTATUS,
  RXBYTEISALIGNED,
  RXBYTEREALIGN,
  RXCDRLOCK,
  RXCHANBONDSEQ,
  RXCHANISALIGNED,
  RXCHANREALIGN,
  RXCHARISCOMMA,
  RXCHARISK,
  RXCHBONDO,
  RXCLKCORCNT,
  RXCOMINITDET,
  RXCOMMADET,
  RXCOMSASDET,
  RXCOMWAKEDET,
  RXDATA,
  RXDATAVALID,
  RXDISPERR,
  RXDLYSRESETDONE,
  RXELECIDLE,
  RXHEADER,
  RXHEADERVALID,
  RXNOTINTABLE,
  RXOSINTDONE,
  RXOSINTSTARTED,
  RXOSINTSTROBEDONE,
  RXOSINTSTROBESTARTED,
  RXOUTCLK,
  RXOUTCLKFABRIC,
  RXOUTCLKPCS,
  RXPHALIGNDONE,
  RXPHMONITOR,
  RXPHSLIPMONITOR,
  RXPMARESETDONE,
  RXPRBSERR,
  RXRATEDONE,
  RXRESETDONE,
  RXSTARTOFSEQ,
  RXSTATUS,
  RXSYNCDONE,
  RXSYNCOUT,
  RXVALID,
  TXBUFSTATUS,
  TXCOMFINISH,
  TXDLYSRESETDONE,
  TXGEARBOXREADY,
  TXOUTCLK,
  TXOUTCLKFABRIC,
  TXOUTCLKPCS,
  TXPHALIGNDONE,
  TXPHINITDONE,
  TXPMARESETDONE,
  TXRATEDONE,
  TXRESETDONE,
  TXSYNCDONE,
  TXSYNCOUT,

  CFGRESET,
  CLKRSVD0,
  CLKRSVD1,
  DMONFIFORESET,
  DMONITORCLK,
  DRPADDR,
  DRPCLK,
  DRPDI,
  DRPEN,
  DRPWE,
  EYESCANMODE,
  EYESCANRESET,
  EYESCANTRIGGER,
  GTPRXN,
  GTPRXP,
  GTRESETSEL,
  GTRSVD,
  GTRXRESET,
  GTTXRESET,
  LOOPBACK,
  PCSRSVDIN,
  PLL0CLK,
  PLL0REFCLK,
  PLL1CLK,
  PLL1REFCLK,
  PMARSVDIN0,
  PMARSVDIN1,
  PMARSVDIN2,
  PMARSVDIN3,
  PMARSVDIN4,
  RESETOVRD,
  RX8B10BEN,
  RXADAPTSELTEST,
  RXBUFRESET,
  RXCDRFREQRESET,
  RXCDRHOLD,
  RXCDROVRDEN,
  RXCDRRESET,
  RXCDRRESETRSV,
  RXCHBONDEN,
  RXCHBONDI,
  RXCHBONDLEVEL,
  RXCHBONDMASTER,
  RXCHBONDSLAVE,
  RXCOMMADETEN,
  RXDDIEN,
  RXDFEXYDEN,
  RXDLYBYPASS,
  RXDLYEN,
  RXDLYOVRDEN,
  RXDLYSRESET,
  RXELECIDLEMODE,
  RXGEARBOXSLIP,
  RXLPMHFHOLD,
  RXLPMHFOVRDEN,
  RXLPMLFHOLD,
  RXLPMLFOVRDEN,
  RXLPMOSINTNTRLEN,
  RXLPMRESET,
  RXMCOMMAALIGNEN,
  RXOOBRESET,
  RXOSCALRESET,
  RXOSHOLD,
  RXOSINTCFG,
  RXOSINTEN,
  RXOSINTHOLD,
  RXOSINTID0,
  RXOSINTNTRLEN,
  RXOSINTOVRDEN,
  RXOSINTPD,
  RXOSINTSTROBE,
  RXOSINTTESTOVRDEN,
  RXOSOVRDEN,
  RXOUTCLKSEL,
  RXPCOMMAALIGNEN,
  RXPCSRESET,
  RXPD,
  RXPHALIGN,
  RXPHALIGNEN,
  RXPHDLYPD,
  RXPHDLYRESET,
  RXPHOVRDEN,
  RXPMARESET,
  RXPOLARITY,
  RXPRBSCNTRESET,
  RXPRBSSEL,
  RXRATE,
  RXRATEMODE,
  RXSLIDE,
  RXSYNCALLIN,
  RXSYNCIN,
  RXSYNCMODE,
  RXSYSCLKSEL,
  RXUSERRDY,
  RXUSRCLK,
  RXUSRCLK2,
  SETERRSTATUS,
  SIGVALIDCLK,
  TSTIN,
  TX8B10BBYPASS,
  TX8B10BEN,
  TXBUFDIFFCTRL,
  TXCHARDISPMODE,
  TXCHARDISPVAL,
  TXCHARISK,
  TXCOMINIT,
  TXCOMSAS,
  TXCOMWAKE,
  TXDATA,
  TXDEEMPH,
  TXDETECTRX,
  TXDIFFCTRL,
  TXDIFFPD,
  TXDLYBYPASS,
  TXDLYEN,
  TXDLYHOLD,
  TXDLYOVRDEN,
  TXDLYSRESET,
  TXDLYUPDOWN,
  TXELECIDLE,
  TXHEADER,
  TXINHIBIT,
  TXMAINCURSOR,
  TXMARGIN,
  TXOUTCLKSEL,
  TXPCSRESET,
  TXPD,
  TXPDELECIDLEMODE,
  TXPHALIGN,
  TXPHALIGNEN,
  TXPHDLYPD,
  TXPHDLYRESET,
  TXPHDLYTSTCLK,
  TXPHINIT,
  TXPHOVRDEN,
  TXPIPPMEN,
  TXPIPPMOVRDEN,
  TXPIPPMPD,
  TXPIPPMSEL,
  TXPIPPMSTEPSIZE,
  TXPISOPD,
  TXPMARESET,
  TXPOLARITY,
  TXPOSTCURSOR,
  TXPOSTCURSORINV,
  TXPRBSFORCEERR,
  TXPRBSSEL,
  TXPRECURSOR,
  TXPRECURSORINV,
  TXRATE,
  TXRATEMODE,
  TXSEQUENCE,
  TXSTARTSEQ,
  TXSWING,
  TXSYNCALLIN,
  TXSYNCIN,
  TXSYNCMODE,
  TXSYSCLKSEL,
  TXUSERRDY,
  TXUSRCLK,
  TXUSRCLK2
);

 `ifdef XIL_TIMING //Simprim
    parameter LOC = "UNPLACED";
 `endif

  parameter [0:0] ACJTAG_DEBUG_MODE = 1'b0;
  parameter [0:0] ACJTAG_MODE = 1'b0;
  parameter [0:0] ACJTAG_RESET = 1'b0;
  parameter [19:0] ADAPT_CFG0 = 20'b00000000000000000000;
  parameter ALIGN_COMMA_DOUBLE = "FALSE";
  parameter [9:0] ALIGN_COMMA_ENABLE = 10'b0001111111;
  parameter integer ALIGN_COMMA_WORD = 1;
  parameter ALIGN_MCOMMA_DET = "TRUE";
  parameter [9:0] ALIGN_MCOMMA_VALUE = 10'b1010000011;
  parameter ALIGN_PCOMMA_DET = "TRUE";
  parameter [9:0] ALIGN_PCOMMA_VALUE = 10'b0101111100;
  parameter CBCC_DATA_SOURCE_SEL = "DECODED";
  parameter [42:0] CFOK_CFG = 43'b1001001000000000000000001000000111010000000;
  parameter [6:0] CFOK_CFG2 = 7'b0100000;
  parameter [6:0] CFOK_CFG3 = 7'b0100000;
  parameter [0:0] CFOK_CFG4 = 1'b0;
  parameter [1:0] CFOK_CFG5 = 2'b00;
  parameter [3:0] CFOK_CFG6 = 4'b0000;
  parameter CHAN_BOND_KEEP_ALIGN = "FALSE";
  parameter integer CHAN_BOND_MAX_SKEW = 7;
  parameter [9:0] CHAN_BOND_SEQ_1_1 = 10'b0101111100;
  parameter [9:0] CHAN_BOND_SEQ_1_2 = 10'b0000000000;
  parameter [9:0] CHAN_BOND_SEQ_1_3 = 10'b0000000000;
  parameter [9:0] CHAN_BOND_SEQ_1_4 = 10'b0000000000;
  parameter [3:0] CHAN_BOND_SEQ_1_ENABLE = 4'b1111;
  parameter [9:0] CHAN_BOND_SEQ_2_1 = 10'b0100000000;
  parameter [9:0] CHAN_BOND_SEQ_2_2 = 10'b0100000000;
  parameter [9:0] CHAN_BOND_SEQ_2_3 = 10'b0100000000;
  parameter [9:0] CHAN_BOND_SEQ_2_4 = 10'b0100000000;
  parameter [3:0] CHAN_BOND_SEQ_2_ENABLE = 4'b1111;
  parameter CHAN_BOND_SEQ_2_USE = "FALSE";
  parameter integer CHAN_BOND_SEQ_LEN = 1;
  parameter [0:0] CLK_COMMON_SWING = 1'b0;
  parameter CLK_CORRECT_USE = "TRUE";
  parameter CLK_COR_KEEP_IDLE = "FALSE";
  parameter integer CLK_COR_MAX_LAT = 20;
  parameter integer CLK_COR_MIN_LAT = 18;
  parameter CLK_COR_PRECEDENCE = "TRUE";
  parameter integer CLK_COR_REPEAT_WAIT = 0;
  parameter [9:0] CLK_COR_SEQ_1_1 = 10'b0100011100;
  parameter [9:0] CLK_COR_SEQ_1_2 = 10'b0000000000;
  parameter [9:0] CLK_COR_SEQ_1_3 = 10'b0000000000;
  parameter [9:0] CLK_COR_SEQ_1_4 = 10'b0000000000;
  parameter [3:0] CLK_COR_SEQ_1_ENABLE = 4'b1111;
  parameter [9:0] CLK_COR_SEQ_2_1 = 10'b0100000000;
  parameter [9:0] CLK_COR_SEQ_2_2 = 10'b0100000000;
  parameter [9:0] CLK_COR_SEQ_2_3 = 10'b0100000000;
  parameter [9:0] CLK_COR_SEQ_2_4 = 10'b0100000000;
  parameter [3:0] CLK_COR_SEQ_2_ENABLE = 4'b1111;
  parameter CLK_COR_SEQ_2_USE = "FALSE";
  parameter integer CLK_COR_SEQ_LEN = 1;
  parameter DEC_MCOMMA_DETECT = "TRUE";
  parameter DEC_PCOMMA_DETECT = "TRUE";
  parameter DEC_VALID_COMMA_ONLY = "TRUE";
  parameter [23:0] DMONITOR_CFG = 24'h000A00;
  parameter [0:0] ES_CLK_PHASE_SEL = 1'b0;
  parameter [5:0] ES_CONTROL = 6'b000000;
  parameter ES_ERRDET_EN = "FALSE";
  parameter ES_EYE_SCAN_EN = "FALSE";
  parameter [11:0] ES_HORZ_OFFSET = 12'h010;
  parameter [9:0] ES_PMA_CFG = 10'b0000000000;
  parameter [4:0] ES_PRESCALE = 5'b00000;
  parameter [79:0] ES_QUALIFIER = 80'h00000000000000000000;
  parameter [79:0] ES_QUAL_MASK = 80'h00000000000000000000;
  parameter [79:0] ES_SDATA_MASK = 80'h00000000000000000000;
  parameter [8:0] ES_VERT_OFFSET = 9'b000000000;
  parameter [3:0] FTS_DESKEW_SEQ_ENABLE = 4'b1111;
  parameter [3:0] FTS_LANE_DESKEW_CFG = 4'b1111;
  parameter FTS_LANE_DESKEW_EN = "FALSE";
  parameter [2:0] GEARBOX_MODE = 3'b000;
  parameter [0:0] IS_CLKRSVD0_INVERTED = 1'b0;
  parameter [0:0] IS_CLKRSVD1_INVERTED = 1'b0;
  parameter [0:0] IS_DMONITORCLK_INVERTED = 1'b0;
  parameter [0:0] IS_DRPCLK_INVERTED = 1'b0;
  parameter [0:0] IS_RXUSRCLK2_INVERTED = 1'b0;
  parameter [0:0] IS_RXUSRCLK_INVERTED = 1'b0;
  parameter [0:0] IS_SIGVALIDCLK_INVERTED = 1'b0;
  parameter [0:0] IS_TXPHDLYTSTCLK_INVERTED = 1'b0;
  parameter [0:0] IS_TXUSRCLK2_INVERTED = 1'b0;
  parameter [0:0] IS_TXUSRCLK_INVERTED = 1'b0;
  parameter [0:0] LOOPBACK_CFG = 1'b0;
  parameter [1:0] OUTREFCLK_SEL_INV = 2'b11;
  parameter PCS_PCIE_EN = "FALSE";
  parameter [47:0] PCS_RSVD_ATTR = 48'h000000000000;
  parameter [11:0] PD_TRANS_TIME_FROM_P2 = 12'h03C;
  parameter [7:0] PD_TRANS_TIME_NONE_P2 = 8'h19;
  parameter [7:0] PD_TRANS_TIME_TO_P2 = 8'h64;
  parameter [0:0] PMA_LOOPBACK_CFG = 1'b0;
  parameter [31:0] PMA_RSV = 32'h00000333;
  parameter [31:0] PMA_RSV2 = 32'h00002050;
  parameter [1:0] PMA_RSV3 = 2'b00;
  parameter [3:0] PMA_RSV4 = 4'b0000;
  parameter [0:0] PMA_RSV5 = 1'b0;
  parameter [0:0] PMA_RSV6 = 1'b0;
  parameter [0:0] PMA_RSV7 = 1'b0;
  parameter [4:0] RXBUFRESET_TIME = 5'b00001;
  parameter RXBUF_ADDR_MODE = "FULL";
  parameter [3:0] RXBUF_EIDLE_HI_CNT = 4'b1000;
  parameter [3:0] RXBUF_EIDLE_LO_CNT = 4'b0000;
  parameter RXBUF_EN = "TRUE";
  parameter RXBUF_RESET_ON_CB_CHANGE = "TRUE";
  parameter RXBUF_RESET_ON_COMMAALIGN = "FALSE";
  parameter RXBUF_RESET_ON_EIDLE = "FALSE";
  parameter RXBUF_RESET_ON_RATE_CHANGE = "TRUE";
  parameter integer RXBUF_THRESH_OVFLW = 61;
  parameter RXBUF_THRESH_OVRD = "FALSE";
  parameter integer RXBUF_THRESH_UNDFLW = 4;
  parameter [4:0] RXCDRFREQRESET_TIME = 5'b00001;
  parameter [4:0] RXCDRPHRESET_TIME = 5'b00001;
  parameter [82:0] RXCDR_CFG = 83'h0000107FE406001041010;
  parameter [0:0] RXCDR_FR_RESET_ON_EIDLE = 1'b0;
  parameter [0:0] RXCDR_HOLD_DURING_EIDLE = 1'b0;
  parameter [5:0] RXCDR_LOCK_CFG = 6'b001001;
  parameter [0:0] RXCDR_PH_RESET_ON_EIDLE = 1'b0;
  parameter [15:0] RXDLY_CFG = 16'h0010;
  parameter [8:0] RXDLY_LCFG = 9'h020;
  parameter [15:0] RXDLY_TAP_CFG = 16'h0000;
  parameter RXGEARBOX_EN = "FALSE";
  parameter [4:0] RXISCANRESET_TIME = 5'b00001;
  parameter [6:0] RXLPMRESET_TIME = 7'b0001111;
  parameter [0:0] RXLPM_BIAS_STARTUP_DISABLE = 1'b0;
  parameter [3:0] RXLPM_CFG = 4'b0110;
  parameter [0:0] RXLPM_CFG1 = 1'b0;
  parameter [0:0] RXLPM_CM_CFG = 1'b0;
  parameter [8:0] RXLPM_GC_CFG = 9'b111100010;
  parameter [2:0] RXLPM_GC_CFG2 = 3'b001;
  parameter [13:0] RXLPM_HF_CFG = 14'b00001111110000;
  parameter [4:0] RXLPM_HF_CFG2 = 5'b01010;
  parameter [3:0] RXLPM_HF_CFG3 = 4'b0000;
  parameter [0:0] RXLPM_HOLD_DURING_EIDLE = 1'b0;
  parameter [0:0] RXLPM_INCM_CFG = 1'b0;
  parameter [0:0] RXLPM_IPCM_CFG = 1'b0;
  parameter [17:0] RXLPM_LF_CFG = 18'b000000001111110000;
  parameter [4:0] RXLPM_LF_CFG2 = 5'b01010;
  parameter [2:0] RXLPM_OSINT_CFG = 3'b100;
  parameter [6:0] RXOOB_CFG = 7'b0000110;
  parameter RXOOB_CLK_CFG = "PMA";
  parameter [4:0] RXOSCALRESET_TIME = 5'b00011;
  parameter [4:0] RXOSCALRESET_TIMEOUT = 5'b00000;
  parameter integer RXOUT_DIV = 2;
  parameter [4:0] RXPCSRESET_TIME = 5'b00001;
  parameter [23:0] RXPHDLY_CFG = 24'h084000;
  parameter [23:0] RXPH_CFG = 24'hC00002;
  parameter [4:0] RXPH_MONITOR_SEL = 5'b00000;
  parameter [2:0] RXPI_CFG0 = 3'b000;
  parameter [0:0] RXPI_CFG1 = 1'b0;
  parameter [0:0] RXPI_CFG2 = 1'b0;
  parameter [4:0] RXPMARESET_TIME = 5'b00011;
  parameter [0:0] RXPRBS_ERR_LOOPBACK = 1'b0;
  parameter integer RXSLIDE_AUTO_WAIT = 7;
  parameter RXSLIDE_MODE = "OFF";
  parameter [0:0] RXSYNC_MULTILANE = 1'b0;
  parameter [0:0] RXSYNC_OVRD = 1'b0;
  parameter [0:0] RXSYNC_SKIP_DA = 1'b0;
  parameter [15:0] RX_BIAS_CFG = 16'b0000111100110011;
  parameter [5:0] RX_BUFFER_CFG = 6'b000000;
  parameter integer RX_CLK25_DIV = 7;
  parameter [0:0] RX_CLKMUX_EN = 1'b1;
  parameter [1:0] RX_CM_SEL = 2'b11;
  parameter [3:0] RX_CM_TRIM = 4'b0100;
  parameter integer RX_DATA_WIDTH = 20;
  parameter [5:0] RX_DDI_SEL = 6'b000000;
  parameter [13:0] RX_DEBUG_CFG = 14'b00000000000000;
  parameter RX_DEFER_RESET_BUF_EN = "TRUE";
  parameter RX_DISPERR_SEQ_MATCH = "TRUE";
  parameter [12:0] RX_OS_CFG = 13'b0001111110000;
  parameter integer RX_SIG_VALID_DLY = 10;
  parameter RX_XCLK_SEL = "RXREC";
  parameter integer SAS_MAX_COM = 64;
  parameter integer SAS_MIN_COM = 36;
  parameter [3:0] SATA_BURST_SEQ_LEN = 4'b1111;
  parameter [2:0] SATA_BURST_VAL = 3'b100;
  parameter [2:0] SATA_EIDLE_VAL = 3'b100;
  parameter integer SATA_MAX_BURST = 8;
  parameter integer SATA_MAX_INIT = 21;
  parameter integer SATA_MAX_WAKE = 7;
  parameter integer SATA_MIN_BURST = 4;
  parameter integer SATA_MIN_INIT = 12;
  parameter integer SATA_MIN_WAKE = 4;
  parameter SATA_PLL_CFG = "VCO_3000MHZ";
  parameter SHOW_REALIGN_COMMA = "TRUE";
  parameter SIM_RECEIVER_DETECT_PASS = "TRUE";
  parameter SIM_RESET_SPEEDUP = "TRUE";
  parameter SIM_TX_EIDLE_DRIVE_LEVEL = "X";
  parameter SIM_VERSION = "1.0";
  parameter [14:0] TERM_RCAL_CFG = 15'b100001000010000;
  parameter [2:0] TERM_RCAL_OVRD = 3'b000;
  parameter [7:0] TRANS_TIME_RATE = 8'h0E;
  parameter [31:0] TST_RSV = 32'h00000000;
  parameter TXBUF_EN = "TRUE";
  parameter TXBUF_RESET_ON_RATE_CHANGE = "FALSE";
  parameter [15:0] TXDLY_CFG = 16'h0010;
  parameter [8:0] TXDLY_LCFG = 9'h020;
  parameter [15:0] TXDLY_TAP_CFG = 16'h0000;
  parameter TXGEARBOX_EN = "FALSE";
  parameter [0:0] TXOOB_CFG = 1'b0;
  parameter integer TXOUT_DIV = 2;
  parameter [4:0] TXPCSRESET_TIME = 5'b00001;
  parameter [23:0] TXPHDLY_CFG = 24'h084000;
  parameter [15:0] TXPH_CFG = 16'h0400;
  parameter [4:0] TXPH_MONITOR_SEL = 5'b00000;
  parameter [1:0] TXPI_CFG0 = 2'b00;
  parameter [1:0] TXPI_CFG1 = 2'b00;
  parameter [1:0] TXPI_CFG2 = 2'b00;
  parameter [0:0] TXPI_CFG3 = 1'b0;
  parameter [0:0] TXPI_CFG4 = 1'b0;
  parameter [2:0] TXPI_CFG5 = 3'b000;
  parameter [0:0] TXPI_GREY_SEL = 1'b0;
  parameter [0:0] TXPI_INVSTROBE_SEL = 1'b0;
  parameter TXPI_PPMCLK_SEL = "TXUSRCLK2";
  parameter [7:0] TXPI_PPM_CFG = 8'b00000000;
  parameter [2:0] TXPI_SYNFREQ_PPM = 3'b000;
  parameter [4:0] TXPMARESET_TIME = 5'b00001;
  parameter [0:0] TXSYNC_MULTILANE = 1'b0;
  parameter [0:0] TXSYNC_OVRD = 1'b0;
  parameter [0:0] TXSYNC_SKIP_DA = 1'b0;
  parameter integer TX_CLK25_DIV = 7;
  parameter [0:0] TX_CLKMUX_EN = 1'b1;
  parameter integer TX_DATA_WIDTH = 20;
  parameter [5:0] TX_DEEMPH0 = 6'b000000;
  parameter [5:0] TX_DEEMPH1 = 6'b000000;
  parameter TX_DRIVE_MODE = "DIRECT";
  parameter [2:0] TX_EIDLE_ASSERT_DELAY = 3'b110;
  parameter [2:0] TX_EIDLE_DEASSERT_DELAY = 3'b100;
  parameter TX_LOOPBACK_DRIVE_HIZ = "FALSE";
  parameter [0:0] TX_MAINCURSOR_SEL = 1'b0;
  parameter [6:0] TX_MARGIN_FULL_0 = 7'b1001110;
  parameter [6:0] TX_MARGIN_FULL_1 = 7'b1001001;
  parameter [6:0] TX_MARGIN_FULL_2 = 7'b1000101;
  parameter [6:0] TX_MARGIN_FULL_3 = 7'b1000010;
  parameter [6:0] TX_MARGIN_FULL_4 = 7'b1000000;
  parameter [6:0] TX_MARGIN_LOW_0 = 7'b1000110;
  parameter [6:0] TX_MARGIN_LOW_1 = 7'b1000100;
  parameter [6:0] TX_MARGIN_LOW_2 = 7'b1000010;
  parameter [6:0] TX_MARGIN_LOW_3 = 7'b1000000;
  parameter [6:0] TX_MARGIN_LOW_4 = 7'b1000000;
  parameter [0:0] TX_PREDRIVER_MODE = 1'b0;
  parameter [13:0] TX_RXDETECT_CFG = 14'h1832;
  parameter [2:0] TX_RXDETECT_REF = 3'b100;
  parameter TX_XCLK_SEL = "TXUSR";
  parameter [0:0] UCODEER_CLR = 1'b0;
  parameter [0:0] USE_PCS_CLK_PHASE_SEL = 1'b0; 

  output DRPRDY;
  output EYESCANDATAERROR;
  output GTPTXN;
  output GTPTXP;
  output PHYSTATUS;
  output PMARSVDOUT0;
  output PMARSVDOUT1;
  output RXBYTEISALIGNED;
  output RXBYTEREALIGN;
  output RXCDRLOCK;
  output RXCHANBONDSEQ;
  output RXCHANISALIGNED;
  output RXCHANREALIGN;
  output RXCOMINITDET;
  output RXCOMMADET;
  output RXCOMSASDET;
  output RXCOMWAKEDET;
  output RXDLYSRESETDONE;
  output RXELECIDLE;
  output RXHEADERVALID;
  output RXOSINTDONE;
  output RXOSINTSTARTED;
  output RXOSINTSTROBEDONE;
  output RXOSINTSTROBESTARTED;
  output RXOUTCLK;
  output RXOUTCLKFABRIC;
  output RXOUTCLKPCS;
  output RXPHALIGNDONE;
  output RXPMARESETDONE;
  output RXPRBSERR;
  output RXRATEDONE;
  output RXRESETDONE;
  output RXSYNCDONE;
  output RXSYNCOUT;
  output RXVALID;
  output TXCOMFINISH;
  output TXDLYSRESETDONE;
  output TXGEARBOXREADY;
  output TXOUTCLK;
  output TXOUTCLKFABRIC;
  output TXOUTCLKPCS;
  output TXPHALIGNDONE;
  output TXPHINITDONE;
  output TXPMARESETDONE;
  output TXRATEDONE;
  output TXRESETDONE;
  output TXSYNCDONE;
  output TXSYNCOUT;
  output [14:0] DMONITOROUT;
  output [15:0] DRPDO;
  output [15:0] PCSRSVDOUT;
  output [1:0] RXCLKCORCNT;
  output [1:0] RXDATAVALID;
  output [1:0] RXSTARTOFSEQ;
  output [1:0] TXBUFSTATUS;
  output [2:0] RXBUFSTATUS;
  output [2:0] RXHEADER;
  output [2:0] RXSTATUS;
  output [31:0] RXDATA;
  output [3:0] RXCHARISCOMMA;
  output [3:0] RXCHARISK;
  output [3:0] RXCHBONDO;
  output [3:0] RXDISPERR;
  output [3:0] RXNOTINTABLE;
  output [4:0] RXPHMONITOR;
  output [4:0] RXPHSLIPMONITOR;

  input CFGRESET;
  input CLKRSVD0;
  input CLKRSVD1;
  input DMONFIFORESET;
  input DMONITORCLK;
  input DRPCLK;
  input DRPEN;
  input DRPWE;
  input EYESCANMODE;
  input EYESCANRESET;
  input EYESCANTRIGGER;
  input GTPRXN;
  input GTPRXP;
  input GTRESETSEL;
  input GTRXRESET;
  input GTTXRESET;
  input PLL0CLK;
  input PLL0REFCLK;
  input PLL1CLK;
  input PLL1REFCLK;
  input PMARSVDIN0;
  input PMARSVDIN1;
  input PMARSVDIN2;
  input PMARSVDIN3;
  input PMARSVDIN4;
  input RESETOVRD;
  input RX8B10BEN;
  input RXBUFRESET;
  input RXCDRFREQRESET;
  input RXCDRHOLD;
  input RXCDROVRDEN;
  input RXCDRRESET;
  input RXCDRRESETRSV;
  input RXCHBONDEN;
  input RXCHBONDMASTER;
  input RXCHBONDSLAVE;
  input RXCOMMADETEN;
  input RXDDIEN;
  input RXDFEXYDEN;
  input RXDLYBYPASS;
  input RXDLYEN;
  input RXDLYOVRDEN;
  input RXDLYSRESET;
  input RXGEARBOXSLIP;
  input RXLPMHFHOLD;
  input RXLPMHFOVRDEN;
  input RXLPMLFHOLD;
  input RXLPMLFOVRDEN;
  input RXLPMOSINTNTRLEN;
  input RXLPMRESET;
  input RXMCOMMAALIGNEN;
  input RXOOBRESET;
  input RXOSCALRESET;
  input RXOSHOLD;
  input RXOSINTEN;
  input RXOSINTHOLD;
  input RXOSINTNTRLEN;
  input RXOSINTOVRDEN;
  input RXOSINTPD;
  input RXOSINTSTROBE;
  input RXOSINTTESTOVRDEN;
  input RXOSOVRDEN;
  input RXPCOMMAALIGNEN;
  input RXPCSRESET;
  input RXPHALIGN;
  input RXPHALIGNEN;
  input RXPHDLYPD;
  input RXPHDLYRESET;
  input RXPHOVRDEN;
  input RXPMARESET;
  input RXPOLARITY;
  input RXPRBSCNTRESET;
  input RXRATEMODE;
  input RXSLIDE;
  input RXSYNCALLIN;
  input RXSYNCIN;
  input RXSYNCMODE;
  input RXUSERRDY;
  input RXUSRCLK2;
  input RXUSRCLK;
  input SETERRSTATUS;
  input SIGVALIDCLK;
  input TX8B10BEN;
  input TXCOMINIT;
  input TXCOMSAS;
  input TXCOMWAKE;
  input TXDEEMPH;
  input TXDETECTRX;
  input TXDIFFPD;
  input TXDLYBYPASS;
  input TXDLYEN;
  input TXDLYHOLD;
  input TXDLYOVRDEN;
  input TXDLYSRESET;
  input TXDLYUPDOWN;
  input TXELECIDLE;
  input TXINHIBIT;
  input TXPCSRESET;
  input TXPDELECIDLEMODE;
  input TXPHALIGN;
  input TXPHALIGNEN;
  input TXPHDLYPD;
  input TXPHDLYRESET;
  input TXPHDLYTSTCLK;
  input TXPHINIT;
  input TXPHOVRDEN;
  input TXPIPPMEN;
  input TXPIPPMOVRDEN;
  input TXPIPPMPD;
  input TXPIPPMSEL;
  input TXPISOPD;
  input TXPMARESET;
  input TXPOLARITY;
  input TXPOSTCURSORINV;
  input TXPRBSFORCEERR;
  input TXPRECURSORINV;
  input TXRATEMODE;
  input TXSTARTSEQ;
  input TXSWING;
  input TXSYNCALLIN;
  input TXSYNCIN;
  input TXSYNCMODE;
  input TXUSERRDY;
  input TXUSRCLK2;
  input TXUSRCLK;
  input [13:0] RXADAPTSELTEST;
  input [15:0] DRPDI;
  input [15:0] GTRSVD;
  input [15:0] PCSRSVDIN;
  input [19:0] TSTIN;
  input [1:0] RXELECIDLEMODE;
  input [1:0] RXPD;
  input [1:0] RXSYSCLKSEL;
  input [1:0] TXPD;
  input [1:0] TXSYSCLKSEL;
  input [2:0] LOOPBACK;
  input [2:0] RXCHBONDLEVEL;
  input [2:0] RXOUTCLKSEL;
  input [2:0] RXPRBSSEL;
  input [2:0] RXRATE;
  input [2:0] TXBUFDIFFCTRL;
  input [2:0] TXHEADER;
  input [2:0] TXMARGIN;
  input [2:0] TXOUTCLKSEL;
  input [2:0] TXPRBSSEL;
  input [2:0] TXRATE;
  input [31:0] TXDATA;
  input [3:0] RXCHBONDI;
  input [3:0] RXOSINTCFG;
  input [3:0] RXOSINTID0;
  input [3:0] TX8B10BBYPASS;
  input [3:0] TXCHARDISPMODE;
  input [3:0] TXCHARDISPVAL;
  input [3:0] TXCHARISK;
  input [3:0] TXDIFFCTRL;
  input [4:0] TXPIPPMSTEPSIZE;
  input [4:0] TXPOSTCURSOR;
  input [4:0] TXPRECURSOR;
  input [6:0] TXMAINCURSOR;
  input [6:0] TXSEQUENCE;
  input [8:0] DRPADDR;

   wire delay_CLKRSVD0;
   wire delay_CLKRSVD1;
   wire delay_DMONITORCLK;
   wire delay_DRPCLK;
   wire delay_RXUSRCLK;
   wire delay_RXUSRCLK2;
   wire delay_SIGVALIDCLK;
   wire delay_TXPHDLYTSTCLK;
   wire delay_TXUSRCLK;
   wire delay_TXUSRCLK2;
   
   assign delay_CLKRSVD0 = CLKRSVD0 ^ IS_CLKRSVD0_INVERTED;
   assign delay_CLKRSVD1 = CLKRSVD1 ^ IS_CLKRSVD1_INVERTED;
   assign delay_DMONITORCLK = DMONITORCLK ^ IS_DMONITORCLK_INVERTED;
   assign delay_DRPCLK = DRPCLK ^ IS_DRPCLK_INVERTED;
   assign delay_RXUSRCLK = RXUSRCLK ^ IS_RXUSRCLK_INVERTED;
   assign delay_RXUSRCLK2 = RXUSRCLK2 ^ IS_RXUSRCLK2_INVERTED;
   assign delay_SIGVALIDCLK = SIGVALIDCLK ^  IS_SIGVALIDCLK_INVERTED;
   assign delay_TXPHDLYTSTCLK = TXPHDLYTSTCLK ^ IS_TXPHDLYTSTCLK_INVERTED;
   assign delay_TXUSRCLK = TXUSRCLK ^ IS_TXUSRCLK_INVERTED;
   assign delay_TXUSRCLK2 = TXUSRCLK2 ^ IS_TXUSRCLK2_INVERTED;
   
   GTPE2_CHANNEL_bb inst_bb (
               .DMONITOROUT(DMONITOROUT),
               .DRPDO(DRPDO),
               .DRPRDY(DRPRDY),
               .EYESCANDATAERROR(EYESCANDATAERROR),
               .GTPTXN(GTPTXN),
               .GTPTXP(GTPTXP),
               .PCSRSVDOUT(PCSRSVDOUT),
               .PHYSTATUS(PHYSTATUS),
               .PMARSVDOUT0(PMARSVDOUT0),
               .PMARSVDOUT1(PMARSVDOUT1),
               .RXBUFSTATUS(RXBUFSTATUS),
               .RXBYTEISALIGNED(RXBYTEISALIGNED),
               .RXBYTEREALIGN(RXBYTEREALIGN),
               .RXCDRLOCK(RXCDRLOCK),
               .RXCHANBONDSEQ(RXCHANBONDSEQ),
               .RXCHANISALIGNED(RXCHANISALIGNED),
               .RXCHANREALIGN(RXCHANREALIGN),
               .RXCHARISCOMMA(RXCHARISCOMMA),
               .RXCHARISK(RXCHARISK),
               .RXCHBONDO(RXCHBONDO),
               .RXCLKCORCNT(RXCLKCORCNT),
               .RXCOMINITDET(RXCOMINITDET),
               .RXCOMMADET(RXCOMMADET),
               .RXCOMSASDET(RXCOMSASDET),
               .RXCOMWAKEDET(RXCOMWAKEDET),
               .RXDATA(RXDATA),
               .RXDATAVALID(RXDATAVALID),
               .RXDISPERR(RXDISPERR),
               .RXDLYSRESETDONE(RXDLYSRESETDONE),
               .RXELECIDLE(RXELECIDLE),
               .RXHEADER(RXHEADER),
               .RXHEADERVALID(RXHEADERVALID),
               .RXNOTINTABLE(RXNOTINTABLE),
               .RXOSINTDONE(RXOSINTDONE),
               .RXOSINTSTARTED(RXOSINTSTARTED),
               .RXOSINTSTROBEDONE(RXOSINTSTROBEDONE),
               .RXOSINTSTROBESTARTED(RXOSINTSTROBESTARTED),
               .RXOUTCLK(RXOUTCLK),
               .RXOUTCLKFABRIC(RXOUTCLKFABRIC),
               .RXOUTCLKPCS(RXOUTCLKPCS),
               .RXPHALIGNDONE(RXPHALIGNDONE),
               .RXPHMONITOR(RXPHMONITOR),
               .RXPHSLIPMONITOR(RXPHSLIPMONITOR),
               .RXPMARESETDONE(RXPMARESETDONE),
               .RXPRBSERR(RXPRBSERR),
               .RXRATEDONE(RXRATEDONE),
               .RXRESETDONE(RXRESETDONE),
               .RXSTARTOFSEQ(RXSTARTOFSEQ),
               .RXSTATUS(RXSTATUS),
               .RXSYNCDONE(RXSYNCDONE),
               .RXSYNCOUT(RXSYNCOUT),
               .RXVALID(RXVALID),
               .TXBUFSTATUS(TXBUFSTATUS),
               .TXCOMFINISH(TXCOMFINISH),
               .TXDLYSRESETDONE(TXDLYSRESETDONE),
               .TXGEARBOXREADY(TXGEARBOXREADY),
               .TXOUTCLK(TXOUTCLK),
               .TXOUTCLKFABRIC(TXOUTCLKFABRIC),
               .TXOUTCLKPCS(TXOUTCLKPCS),
               .TXPHALIGNDONE(TXPHALIGNDONE),
               .TXPHINITDONE(TXPHINITDONE),
               .TXPMARESETDONE(TXPMARESETDONE),
               .TXRATEDONE(TXRATEDONE),
               .TXRESETDONE(TXRESETDONE),
               .TXSYNCDONE(TXSYNCDONE),
               .TXSYNCOUT(TXSYNCOUT),
               .CFGRESET(CFGRESET),
               .CLKRSVD0(delay_CLKRSVD0),
               .CLKRSVD1(delay_CLKRSVD1),
               .DMONFIFORESET(DMONFIFORESET),
               .DMONITORCLK(delay_DMONITORCLK),
               .DRPADDR(DRPADDR),
               .DRPCLK(delay_DRPCLK),
               .DRPDI(DRPDI),
               .DRPEN(DRPEN),
               .DRPWE(DRPWE),
               .EYESCANMODE(EYESCANMODE),
               .EYESCANRESET(EYESCANRESET),
               .EYESCANTRIGGER(EYESCANTRIGGER),
               .GTPRXN(GTPRXN),
               .GTPRXP(GTPRXP),
               .GTRESETSEL(GTRESETSEL),
               .GTRSVD(GTRSVD),
               .GTRXRESET(GTRXRESET),
               .GTTXRESET(GTTXRESET),
               .LOOPBACK(LOOPBACK),
               .PCSRSVDIN(PCSRSVDIN),
               .PLL0CLK(PLL0CLK),
               .PLL0REFCLK(PLL0REFCLK),
               .PLL1CLK(PLL1CLK),
               .PLL1REFCLK(PLL1REFCLK),
               .PMARSVDIN0(PMARSVDIN0),
               .PMARSVDIN1(PMARSVDIN1),
               .PMARSVDIN2(PMARSVDIN2),
               .PMARSVDIN3(PMARSVDIN3),
               .PMARSVDIN4(PMARSVDIN4),
               .RESETOVRD(RESETOVRD),
               .RX8B10BEN(RX8B10BEN),
               .RXADAPTSELTEST(RXADAPTSELTEST),
               .RXBUFRESET(RXBUFRESET),
               .RXCDRFREQRESET(RXCDRFREQRESET),
               .RXCDRHOLD(RXCDRHOLD),
               .RXCDROVRDEN(RXCDROVRDEN),
               .RXCDRRESET(RXCDRRESET),
               .RXCDRRESETRSV(RXCDRRESETRSV),
               .RXCHBONDEN(RXCHBONDEN),
               .RXCHBONDI(RXCHBONDI),
               .RXCHBONDLEVEL(RXCHBONDLEVEL),
               .RXCHBONDMASTER(RXCHBONDMASTER),
               .RXCHBONDSLAVE(RXCHBONDSLAVE),
               .RXCOMMADETEN(RXCOMMADETEN),
               .RXDDIEN(RXDDIEN),
               .RXDFEXYDEN(RXDFEXYDEN),
               .RXDLYBYPASS(RXDLYBYPASS),
               .RXDLYEN(RXDLYEN),
               .RXDLYOVRDEN(RXDLYOVRDEN),
               .RXDLYSRESET(RXDLYSRESET),
               .RXELECIDLEMODE(RXELECIDLEMODE),
               .RXGEARBOXSLIP(RXGEARBOXSLIP),
               .RXLPMHFHOLD(RXLPMHFHOLD),
               .RXLPMHFOVRDEN(RXLPMHFOVRDEN),
               .RXLPMLFHOLD(RXLPMLFHOLD),
               .RXLPMLFOVRDEN(RXLPMLFOVRDEN),
               .RXLPMOSINTNTRLEN(RXLPMOSINTNTRLEN),
               .RXLPMRESET(RXLPMRESET),
               .RXMCOMMAALIGNEN(RXMCOMMAALIGNEN),
               .RXOOBRESET(RXOOBRESET),
               .RXOSCALRESET(RXOSCALRESET),
               .RXOSHOLD(RXOSHOLD),
               .RXOSINTCFG(RXOSINTCFG),
               .RXOSINTEN(RXOSINTEN),
               .RXOSINTHOLD(RXOSINTHOLD),
               .RXOSINTID0(RXOSINTID0),
               .RXOSINTNTRLEN(RXOSINTNTRLEN),
               .RXOSINTOVRDEN(RXOSINTOVRDEN),
               .RXOSINTPD(RXOSINTPD),
               .RXOSINTSTROBE(RXOSINTSTROBE),
               .RXOSINTTESTOVRDEN(RXOSINTTESTOVRDEN),
               .RXOSOVRDEN(RXOSOVRDEN),
               .RXOUTCLKSEL(RXOUTCLKSEL),
               .RXPCOMMAALIGNEN(RXPCOMMAALIGNEN),
               .RXPCSRESET(RXPCSRESET),
               .RXPD(RXPD),
               .RXPHALIGN(RXPHALIGN),
               .RXPHALIGNEN(RXPHALIGNEN),
               .RXPHDLYPD(RXPHDLYPD),
               .RXPHDLYRESET(RXPHDLYRESET),
               .RXPHOVRDEN(RXPHOVRDEN),
               .RXPMARESET(RXPMARESET),
               .RXPOLARITY(RXPOLARITY),
               .RXPRBSCNTRESET(RXPRBSCNTRESET),
               .RXPRBSSEL(RXPRBSSEL),
               .RXRATE(RXRATE),
               .RXRATEMODE(RXRATEMODE),
               .RXSLIDE(RXSLIDE),
               .RXSYNCALLIN(RXSYNCALLIN),
               .RXSYNCIN(RXSYNCIN),
               .RXSYNCMODE(RXSYNCMODE),
               .RXSYSCLKSEL(RXSYSCLKSEL),
               .RXUSERRDY(RXUSERRDY),
               .RXUSRCLK(delay_RXUSRCLK),
               .RXUSRCLK2(delay_RXUSRCLK2),
               .SETERRSTATUS(SETERRSTATUS),
               .SIGVALIDCLK(delay_SIGVALIDCLK),
               .TSTIN(TSTIN),
               .TX8B10BBYPASS(TX8B10BBYPASS),
               .TX8B10BEN(TX8B10BEN),
               .TXBUFDIFFCTRL(TXBUFDIFFCTRL),
               .TXCHARDISPMODE(TXCHARDISPMODE),
               .TXCHARDISPVAL(TXCHARDISPVAL),
               .TXCHARISK(TXCHARISK),
               .TXCOMINIT(TXCOMINIT),
               .TXCOMSAS(TXCOMSAS),
               .TXCOMWAKE(TXCOMWAKE),
               .TXDATA(TXDATA),
               .TXDEEMPH(TXDEEMPH),
               .TXDETECTRX(TXDETECTRX),
               .TXDIFFCTRL(TXDIFFCTRL),
               .TXDIFFPD(TXDIFFPD),
               .TXDLYBYPASS(TXDLYBYPASS),
               .TXDLYEN(TXDLYEN),
               .TXDLYHOLD(TXDLYHOLD),
               .TXDLYOVRDEN(TXDLYOVRDEN),
               .TXDLYSRESET(TXDLYSRESET),
               .TXDLYUPDOWN(TXDLYUPDOWN),
               .TXELECIDLE(TXELECIDLE),
               .TXHEADER(TXHEADER),
               .TXINHIBIT(TXINHIBIT),
               .TXMAINCURSOR(TXMAINCURSOR),
               .TXMARGIN(TXMARGIN),
               .TXOUTCLKSEL(TXOUTCLKSEL),
               .TXPCSRESET(TXPCSRESET),
               .TXPD(TXPD),
               .TXPDELECIDLEMODE(TXPDELECIDLEMODE),
               .TXPHALIGN(TXPHALIGN),
               .TXPHALIGNEN(TXPHALIGNEN),
               .TXPHDLYPD(TXPHDLYPD),
               .TXPHDLYRESET(TXPHDLYRESET),
               .TXPHDLYTSTCLK(delay_TXPHDLYTSTCLK),
               .TXPHINIT(TXPHINIT),
               .TXPHOVRDEN(TXPHOVRDEN),
               .TXPIPPMEN(TXPIPPMEN),
               .TXPIPPMOVRDEN(TXPIPPMOVRDEN),
               .TXPIPPMPD(TXPIPPMPD),
               .TXPIPPMSEL(TXPIPPMSEL),
               .TXPIPPMSTEPSIZE(TXPIPPMSTEPSIZE),
               .TXPISOPD(TXPISOPD),
               .TXPMARESET(TXPMARESET),
               .TXPOLARITY(TXPOLARITY),
               .TXPOSTCURSOR(TXPOSTCURSOR),
               .TXPOSTCURSORINV(TXPOSTCURSORINV),
               .TXPRBSFORCEERR(TXPRBSFORCEERR),
               .TXPRBSSEL(TXPRBSSEL),
               .TXPRECURSOR(TXPRECURSOR),
               .TXPRECURSORINV(TXPRECURSORINV),
               .TXRATE(TXRATE),
               .TXRATEMODE(TXRATEMODE),
               .TXSEQUENCE(TXSEQUENCE),
               .TXSTARTSEQ(TXSTARTSEQ),
               .TXSWING(TXSWING),
               .TXSYNCALLIN(TXSYNCALLIN),
               .TXSYNCIN(TXSYNCIN),
               .TXSYNCMODE(TXSYNCMODE),
               .TXSYSCLKSEL(TXSYSCLKSEL),
               .TXUSERRDY(TXUSERRDY),
               .TXUSRCLK(delay_TXUSRCLK),
               .TXUSRCLK2(delay_TXUSRCLK2)
               );

endmodule

module GTPE2_CHANNEL_bb (
  output DRPRDY,
  output EYESCANDATAERROR,
  output GTPTXN,
  output GTPTXP,
  output PHYSTATUS,
  output PMARSVDOUT0,
  output PMARSVDOUT1,
  output RXBYTEISALIGNED,
  output RXBYTEREALIGN,
  output RXCDRLOCK,
  output RXCHANBONDSEQ,
  output RXCHANISALIGNED,
  output RXCHANREALIGN,
  output RXCOMINITDET,
  output RXCOMMADET,
  output RXCOMSASDET,
  output RXCOMWAKEDET,
  output RXDLYSRESETDONE,
  output RXELECIDLE,
  output RXHEADERVALID,
  output RXOSINTDONE,
  output RXOSINTSTARTED,
  output RXOSINTSTROBEDONE,
  output RXOSINTSTROBESTARTED,
  output RXOUTCLK,
  output RXOUTCLKFABRIC,
  output RXOUTCLKPCS,
  output RXPHALIGNDONE,
  output RXPMARESETDONE,
  output RXPRBSERR,
  output RXRATEDONE,
  output RXRESETDONE,
  output RXSYNCDONE,
  output RXSYNCOUT,
  output RXVALID,
  output TXCOMFINISH,
  output TXDLYSRESETDONE,
  output TXGEARBOXREADY,
  output TXOUTCLK,
  output TXOUTCLKFABRIC,
  output TXOUTCLKPCS,
  output TXPHALIGNDONE,
  output TXPHINITDONE,
  output TXPMARESETDONE,
  output TXRATEDONE,
  output TXRESETDONE,
  output TXSYNCDONE,
  output TXSYNCOUT,
  output [14:0] DMONITOROUT,
  output [15:0] DRPDO,
  output [15:0] PCSRSVDOUT,
  output [1:0] RXCLKCORCNT,
  output [1:0] RXDATAVALID,
  output [1:0] RXSTARTOFSEQ,
  output [1:0] TXBUFSTATUS,
  output [2:0] RXBUFSTATUS,
  output [2:0] RXHEADER,
  output [2:0] RXSTATUS,
  output [31:0] RXDATA,
  output [3:0] RXCHARISCOMMA,
  output [3:0] RXCHARISK,
  output [3:0] RXCHBONDO,
  output [3:0] RXDISPERR,
  output [3:0] RXNOTINTABLE,
  output [4:0] RXPHMONITOR,
  output [4:0] RXPHSLIPMONITOR,

  input CFGRESET,
  input CLKRSVD0,
  input CLKRSVD1,
  input DMONFIFORESET,
  input DMONITORCLK,
  input DRPCLK,
  input DRPEN,
  input DRPWE,
  input EYESCANMODE,
  input EYESCANRESET,
  input EYESCANTRIGGER,
  input GTPRXN,
  input GTPRXP,
  input GTRESETSEL,
  input GTRXRESET,
  input GTTXRESET,
  input PLL0CLK,
  input PLL0REFCLK,
  input PLL1CLK,
  input PLL1REFCLK,
  input PMARSVDIN0,
  input PMARSVDIN1,
  input PMARSVDIN2,
  input PMARSVDIN3,
  input PMARSVDIN4,
  input RESETOVRD,
  input RX8B10BEN,
  input RXBUFRESET,
  input RXCDRFREQRESET,
  input RXCDRHOLD,
  input RXCDROVRDEN,
  input RXCDRRESET,
  input RXCDRRESETRSV,
  input RXCHBONDEN,
  input RXCHBONDMASTER,
  input RXCHBONDSLAVE,
  input RXCOMMADETEN,
  input RXDDIEN,
  input RXDFEXYDEN,
  input RXDLYBYPASS,
  input RXDLYEN,
  input RXDLYOVRDEN,
  input RXDLYSRESET,
  input RXGEARBOXSLIP,
  input RXLPMHFHOLD,
  input RXLPMHFOVRDEN,
  input RXLPMLFHOLD,
  input RXLPMLFOVRDEN,
  input RXLPMOSINTNTRLEN,
  input RXLPMRESET,
  input RXMCOMMAALIGNEN,
  input RXOOBRESET,
  input RXOSCALRESET,
  input RXOSHOLD,
  input RXOSINTEN,
  input RXOSINTHOLD,
  input RXOSINTNTRLEN,
  input RXOSINTOVRDEN,
  input RXOSINTPD,
  input RXOSINTSTROBE,
  input RXOSINTTESTOVRDEN,
  input RXOSOVRDEN,
  input RXPCOMMAALIGNEN,
  input RXPCSRESET,
  input RXPHALIGN,
  input RXPHALIGNEN,
  input RXPHDLYPD,
  input RXPHDLYRESET,
  input RXPHOVRDEN,
  input RXPMARESET,
  input RXPOLARITY,
  input RXPRBSCNTRESET,
  input RXRATEMODE,
  input RXSLIDE,
  input RXSYNCALLIN,
  input RXSYNCIN,
  input RXSYNCMODE,
  input RXUSERRDY,
  input RXUSRCLK2,
  input RXUSRCLK,
  input SETERRSTATUS,
  input SIGVALIDCLK,
  input TX8B10BEN,
  input TXCOMINIT,
  input TXCOMSAS,
  input TXCOMWAKE,
  input TXDEEMPH,
  input TXDETECTRX,
  input TXDIFFPD,
  input TXDLYBYPASS,
  input TXDLYEN,
  input TXDLYHOLD,
  input TXDLYOVRDEN,
  input TXDLYSRESET,
  input TXDLYUPDOWN,
  input TXELECIDLE,
  input TXINHIBIT,
  input TXPCSRESET,
  input TXPDELECIDLEMODE,
  input TXPHALIGN,
  input TXPHALIGNEN,
  input TXPHDLYPD,
  input TXPHDLYRESET,
  input TXPHDLYTSTCLK,
  input TXPHINIT,
  input TXPHOVRDEN,
  input TXPIPPMEN,
  input TXPIPPMOVRDEN,
  input TXPIPPMPD,
  input TXPIPPMSEL,
  input TXPISOPD,
  input TXPMARESET,
  input TXPOLARITY,
  input TXPOSTCURSORINV,
  input TXPRBSFORCEERR,
  input TXPRECURSORINV,
  input TXRATEMODE,
  input TXSTARTSEQ,
  input TXSWING,
  input TXSYNCALLIN,
  input TXSYNCIN,
  input TXSYNCMODE,
  input TXUSERRDY,
  input TXUSRCLK2,
  input TXUSRCLK,
  input [13:0] RXADAPTSELTEST,
  input [15:0] DRPDI,
  input [15:0] GTRSVD,
  input [15:0] PCSRSVDIN,
  input [19:0] TSTIN,
  input [1:0] RXELECIDLEMODE,
  input [1:0] RXPD,
  input [1:0] RXSYSCLKSEL,
  input [1:0] TXPD,
  input [1:0] TXSYSCLKSEL,
  input [2:0] LOOPBACK,
  input [2:0] RXCHBONDLEVEL,
  input [2:0] RXOUTCLKSEL,
  input [2:0] RXPRBSSEL,
  input [2:0] RXRATE,
  input [2:0] TXBUFDIFFCTRL,
  input [2:0] TXHEADER,
  input [2:0] TXMARGIN,
  input [2:0] TXOUTCLKSEL,
  input [2:0] TXPRBSSEL,
  input [2:0] TXRATE,
  input [31:0] TXDATA,
  input [3:0] RXCHBONDI,
  input [3:0] RXOSINTCFG,
  input [3:0] RXOSINTID0,
  input [3:0] TX8B10BBYPASS,
  input [3:0] TXCHARDISPMODE,
  input [3:0] TXCHARDISPVAL,
  input [3:0] TXCHARISK,
  input [3:0] TXDIFFCTRL,
  input [4:0] TXPIPPMSTEPSIZE,
  input [4:0] TXPOSTCURSOR,
  input [4:0] TXPRECURSOR,
  input [6:0] TXMAINCURSOR,
  input [6:0] TXSEQUENCE,
  input [8:0] DRPADDR
);

endmodule

`endcelldefine
