
# DART IPs

This repository has a list of ready-to-use hardware IPs and static parts for DART.

## Summary of IPs

[//]: <> (This is a comment.)

The following table summarizes the existing IPs and some of their features.
The columns refer to the existance of software example, the IP hardware description language, if it has a testbench, and if it has been tested in FPGA. Go to each IP directory for their respective documentation.

| IP name                                      | sw ex. | hw lang | tb | FPGA |
|----------------------------------------------|--------|---------|----|------|
| [FIR](ips/fir/readme.md)                     |    N   |   cpp   | Y  |  N   |
| [memcpy](ips/memcpy/readme.md)               |    N   |   cpp   | Y  |  N   |
| [amalthea_prem](ips/amalthea_prem/readme.md) |    N   |   vhd   | Y  |  N   |
| [amalthea_pipe](ips/amalthea_pipe/readme.md) |    N   |   vhd   | Y  |  N   |
| mat_mult                                     |        |         |    |      |
|                                              |        |         |    |      |

## guidelines and structure for IPs

All IPs should follow these guidelines and this structure in order to reuse the scripts and minimize the integration issues with DART and FRED.

### guidelines

 - the IPs must not have automatically genereted files, like files generated by synthesis tools. Use the scripts instead to recreate the design;

### structure 

All IPs must have the following directory structure: 
 
   
```
.
├── hw
│   ├── build.tcl
│   ├── src
│   │   ├── memcpy.cpp
│   │   └── ...
│   └── tb
│       ├── tb.cpp
│       └── ...
├── readme.md
└── sw
    ├── Makefile
    └── src
        ├── memcpy.cpp
        └── ...
```   

 - the *readme.md* file documents the IP, including usage/perfomance/power reports, configuration parameters, etc;
 - the file *hw/build.tcl* is a script synthesis for Vivado (for Verilog or VHDL sources) or for Vivado HLS (for cpp sources). This script refers to the common synthesis script located at the *scripts* directory, at same level of the IP directory;
 - the *sw/Makefile* compiles the example application for the IP;

### running synthesis for the IPs

Go to the directory *ips/<ip-name>/hw* and, for IPs based on HLS, run:


```
$ vivado_hls build.tcl
```   

The generated IP is located in the directory *ips/<ip-name>/hw/<ip-name>/solution_0/impl/ip*.

For IPs based on Verilog or VHDL, run:

```
$ vivado -mode batch -source build.tcl
```

The generated IP is located in the directory *ips/<ip-name>/vivado/<ip-name>.runs/impl_1/*.


## guidelines and structure for the static part of the design

The static part of the FPGA design is the part does not suffers DPR.
All static parts must follow these guidelines and this structure in order to reuse the scripts and minimize the integration issues with DART and FRED.

### guidelines

 - the static parts must not have automatically genereted files, like files generated by synthesis tools. Use the scripts instead to recreate the design;

### structure 

All static parts must have the following directory structure: 

```   
.
├── build.sh
├── LICENSE
├── README.md
├── hw
│   ├── bd
│   │   └── design_1.tcl
│   ├── hdl
│   ├── ips
│   ├── sim
│   └── xdc
└── vivado
```   

 - the *build.sh* script is set to rerun the synthesis to create a vivado design;
 - use the *readme.md* to document the design including, for example, usage/perfomance/power reports;
 - if the static part is based on a block design, this file must be placed in the *hw/bd* directory;
 - if the static part is based on a HDL design, the hardware description files (.vhd and/or .v) must be placed in the *hw/hdl* directory;
 - if there is a testbench, this must be placed in the *hw/sim* directory;
 - if there are constraint files, these must be placed in the *hw/xdc* directory;
 - the IPs under DPR must be linked in the *hw/ips* directory. The default IP is the memcpy IP. Just replace the  symbolic links to point to other IPs directories;

### running synthesis for the static part

Go to the directory *static/<static-name>/* and run:

```
$ vivado -mode batch -source build.tcl
```   

The generated design is located in the *vivado* directory.
The generated DCP file is located in the directory *static/<static-name>/vivado/<proj-name>/<proj-name>.runs/synth_1/<proj-name>_wrapper.dcp.

# Authors

- Alexandre Amory (April 2021), ReTiS Lab, Scuola Sant'Anna, Pisa, Italy.


# Funding

This tool has been developed in the context of the [AMPERE project](https://ampere-euproject.eu/).
This project has received funding from the European Union’s Horizon 2020 
research and innovation programme under grant agreement No 871669.
