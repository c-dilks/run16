# run15
run15 readiness code

## directories
each directory usually has its own readme file

* `fms_map`
  * produces `geotr.root`, which contains a tree with various branches for FMS
    mapping
    * Pb-glass cell coordinates
    * patch panel (pp) coordinates
    * QT coordinates
    * HV coordinates
  * produces `maps.pdf`, which is a series of images of the FMS, where the
    out-of-page axis is one of the branches in `geotr`

* `fmsvoltages2`
  * Thomas Burton's FMS HV and QT bitshift settings code

* `HVscan`
  * code to analyse a set of runs with different HV setpoints
    * produces gain curves
    * produces resolutions as a function of HV

* `survey`
  * uses survey measurements to produce an image of the location of each Pb-glass
    cell, in units of millimeters
