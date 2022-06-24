#set_property SEVERITY {Warning} [get_drc_checks RTSTAT-2]
#clock
set_property PACKAGE_PIN E3 [get_ports clk]
set_property CLOCK_DEDICATED_ROUTE BACKBONE [get_nets clk]
create_clock -period 10.000 -name clk -waveform {0.000 5.000} [get_ports clk]

#reset
set_property PACKAGE_PIN C12 [get_ports resetn]


#led

set_property PACKAGE_PIN H17 [get_ports {led[0]}]
set_property PACKAGE_PIN K15 [get_ports {led[1]}]
set_property PACKAGE_PIN J13 [get_ports {led[2]}]
set_property PACKAGE_PIN N14 [get_ports {led[3]}]
set_property PACKAGE_PIN R18 [get_ports {led[4]}]
set_property PACKAGE_PIN V17 [get_ports {led[5]}]
set_property PACKAGE_PIN U17 [get_ports {led[6]}]
set_property PACKAGE_PIN U16 [get_ports {led[7]}]
set_property PACKAGE_PIN V16 [get_ports {led[8]}]
set_property PACKAGE_PIN T15 [get_ports {led[9]}]
set_property PACKAGE_PIN U14 [get_ports {led[10]}]
set_property PACKAGE_PIN T16 [get_ports {led[11]}]
set_property PACKAGE_PIN V15 [get_ports {led[12]}]
set_property PACKAGE_PIN V14 [get_ports {led[13]}]
set_property PACKAGE_PIN V12 [get_ports {led[14]}]
set_property PACKAGE_PIN V11 [get_ports {led[15]}]

#num

#set_property PACKAGE_PIN H15 :DP
set_property PACKAGE_PIN H15 [get_ports {num_csn[7]}]
set_property PACKAGE_PIN L18 [get_ports {num_csn[6]}]
set_property PACKAGE_PIN T11 [get_ports {num_csn[5]}]
set_property PACKAGE_PIN P15 [get_ports {num_csn[4]}]
set_property PACKAGE_PIN K13 [get_ports {num_csn[3]}]
set_property PACKAGE_PIN K16 [get_ports {num_csn[2]}]
set_property PACKAGE_PIN R10 [get_ports {num_csn[1]}]
set_property PACKAGE_PIN T10 [get_ports {num_csn[0]}]

set_property PACKAGE_PIN U13 [get_ports {num_an[7]}]
set_property PACKAGE_PIN K2 [get_ports {num_an[6]}]
set_property PACKAGE_PIN T14 [get_ports {num_an[5]}]
set_property PACKAGE_PIN P14 [get_ports {num_an[4]}]
set_property PACKAGE_PIN J14 [get_ports {num_an[3]}]
set_property PACKAGE_PIN T9 [get_ports {num_an[2]}]
set_property PACKAGE_PIN J18 [get_ports {num_an[1]}]
set_property PACKAGE_PIN J17 [get_ports {num_an[0]}]

#switch

set_property PACKAGE_PIN V10 [get_ports {switch[15]}]
set_property PACKAGE_PIN U11 [get_ports {switch[14]}]
set_property PACKAGE_PIN U12 [get_ports {switch[13]}]
set_property PACKAGE_PIN H6 [get_ports {switch[12]}]
set_property PACKAGE_PIN T13 [get_ports {switch[11]}]
set_property PACKAGE_PIN R16 [get_ports {switch[10]}]
set_property PACKAGE_PIN U8 [get_ports {switch[9]}]
set_property PACKAGE_PIN T8 [get_ports {switch[8]}]
set_property PACKAGE_PIN R13 [get_ports {switch[7]}]
set_property PACKAGE_PIN U18 [get_ports {switch[6]}]
set_property PACKAGE_PIN T18 [get_ports {switch[5]}]
set_property PACKAGE_PIN R17 [get_ports {switch[4]}]
set_property PACKAGE_PIN R15 [get_ports {switch[3]}]
set_property PACKAGE_PIN M13 [get_ports {switch[2]}]
set_property PACKAGE_PIN L16 [get_ports {switch[1]}]
set_property PACKAGE_PIN J15 [get_ports {switch[0]}]

#led (tri-col)

# rgb rgb
set_property PACKAGE_PIN N16 [get_ports {rgb1[2]}]
set_property PACKAGE_PIN R11 [get_ports {rgb1[1]}]
set_property PACKAGE_PIN G14 [get_ports {rgb1[0]}]
set_property PACKAGE_PIN N15 [get_ports {rgb2[2]}]
set_property PACKAGE_PIN M16 [get_ports {rgb2[1]}]
set_property PACKAGE_PIN R12 [get_ports {rgb2[0]}]

#button

# right
set_property PACKAGE_PIN M17 [get_ports {button[4]}]
# up
set_property PACKAGE_PIN M18 [get_ports {button[3]}]
# left
set_property PACKAGE_PIN P17 [get_ports {button[2]}]
# down
set_property PACKAGE_PIN P18 [get_ports {button[1]}]
# mid
set_property PACKAGE_PIN N17 [get_ports {button[0]}]

#standard

set_property IOSTANDARD LVCMOS33 [get_ports clk]
set_property IOSTANDARD LVCMOS33 [get_ports resetn]
set_property IOSTANDARD LVCMOS33 [get_ports {led[*]}]

set_property IOSTANDARD LVCMOS33 [get_ports {rgb1[*]}]
set_property IOSTANDARD LVCMOS33 [get_ports {rgb2[*]}]

set_property IOSTANDARD LVCMOS33 [get_ports {num_csn[*]}]
set_property IOSTANDARD LVCMOS33 [get_ports {num_an[*]}]
set_property IOSTANDARD LVCMOS33 [get_ports {switch[*]}]
set_property IOSTANDARD LVCMOS33 [get_ports {button[*]}]

#set_false_path -from [get_clocks -of_objects [get_pins pll.clk_pll/inst/plle2_adv_inst/CLKOUT1]] -to [get_clocks -of_objects [get_pins pll.clk_pll/inst/plle2_adv_inst/CLKOUT0]]
#set_false_path -from [get_clocks -of_objects [get_pins pll.clk_pll/inst/plle2_adv_inst/CLKOUT0]] -to [get_clocks -of_objects [get_pins pll.clk_pll/inst/plle2_adv_inst/CLKOUT1]]

