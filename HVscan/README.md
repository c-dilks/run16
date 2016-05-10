# run15/HVscan
analyses a set of runs with different HV setpoints

* `hv_scan.C`
  * when you run `DoRun` on `onl` machine, it will produce a subdirectory
    in the same directory as `DoRun`, called `[runnum].[segnum]`; this directory
    must be copied to `run15/HVscan`, for each run, in order to execute this script
  * you first must define a list of run numbers and HV set points near the
    top of the script
    * set `NUM` to be the number of runs to analyse
    * set `runnum[*]` to be each runnum
    * set `largehv[*]` to be the large cell HV setpoint in units kV
    * set `smallhv[*]` to be the small cell HV setpoints in hexadecimal
    * I also prefer to comment whether STAR magnet is on/off
  * in the main for loop, there is a comment section that says `DEBUG`; if this
    is commented out, the entire for loop will execute (which may take a while).
    Uncomment this section to run a shorter for loop for faster testing
  * output files:
    * `hvtr.root` contains two `TTrees`
      * `hvtr` contains fit results for the gain curve for each channel
      * `adcdisttr` contains fit results for each adc distribution
    * subdirectory `adc_dists` contains png files for the adc distributions
    * subdirectory `gain_curves` contains png files for the gain curves

* `draw_gain_fit_params.C`
  * reads `hvtr.root` and produces `gain_file_params.root`, which contains:
    * FMS display canvases for the fit parameters and chisq/ndf for gain curves
    * distributions of `alpha` for each `cell_type`

* `make_calibration_files.C`
  * builds `large_gaincurve_par.txt` and `small_gaincurve_par.txt`, which are files
    used for Thomas Burton's fmsvoltages software; they are library files with columns
    `[nstb] [row] [col] [scale] [alpha]`, where `scale` and `alpha` are gain curve 
    fit parameters

* `draw_LED_resolutions.C`
  * reads `hvtr.root`
  * in the chain of if statements, you must provide a list of large HV and small
    HV setpoint pairs; run numbers are not needed; the statement with `day==0`
    is the default executed block, so if you add a new if statement, it might
    be wise to move the `day==0` condition to that new block
    * `NUM` is the number of setpoint pairs
      * if there are different number of setpoints for large and for small cells,
        separately define `NUM_large` and `NUM_small`
    * `Lhv_lb` and `Lhv_ub` are lower and upper bounds for large cell setpoints
      * should be half a bin width lower (higher) than smallest (largest) setpoint
    * `Shv_lb` and `Shv_ub` are lower and upper bounds for small cell setpoints
      * should be half a bin width lower (higher) than smallest (largest) setpoint
    * `extra_cuts` are useful for tuning and filtering out any junk fits
  * outputs `res.root`, containing:
    * chisq/ndf distributions for adc distribution gaussian fits
    * 2d-hist for ADC mean vs. HV setpoint
    * 2d-hist for ADC sigma (rms) vs. HV setpoint
    * 2d-hist for ADC resolution (sigma/mean) vs. HV setpoint
    * FMS display canvas for resolutions

* other scripts
  * `evdisp12.C`: my local backup of this script from onl machine; this was
    the first update of this script I wrote to include channel numbers and
    guide lines on the FMS display canvas
  * `magent_ratio.C`: used for a specific run to compare ADC values when the 
    STAR magnet was on to when it was off; this was a one-time use script
  * `small_cell_LUT.C`: uses a calculation in heppel's small cell `console.exe`
    to convert small cell HV set point in hexadecimal to expcected HV setting in 
    volts; I'm not sure if this is correct
  * `plot_small_cell_LUT.C`: plots small cell HV setpoint in volts vs. that in hex,
    using the calculation in `small_cell_LUT.C`

