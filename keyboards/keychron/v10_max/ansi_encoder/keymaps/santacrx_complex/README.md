# @santacrx's Keychron V10 Firmware mod

> Note: This is a port of my [V10 firmware](https://github.com/santacrx/qmk_firmware/tree/santacrx_v10/keyboards/keychron/v10/ansi_encoder/keymaps/santacrx_complex) for my V10 Max.
> Most of this ReadMe is the same as the V10's, except where differences in design or implementation were needed.
> This is a separate repo branched off of Keychron's as QMK does not have the Max in there.

This is my customization for my v10 to maximize the capabilities plus visuals I wanted. 
This keymap has custom lighting per layer based on what the layer contents are. 
This is a spin-off of my original keymap, with a more complex change of states using the knob, thus freeing the key to the right of the rh spacebar for something else.

Basic function coloring is  still kept from `santacrx_layers`, but this is playground for using the knob to change macro and knob functionality without changing the basic keyboard ones. 
I can have different macro layers available for regular typing, one for LabVIEW use, one for Excel & MATLAB/Simulink, one for VSCODE, and one for CAD, plus an extra one as a placeholder for future value. 
I still have the qwerty layer and the numpad/mouse layer.
~Also the original OS switch at the back is now mapped to lights on/off.~
(Not on the V10 Max due to conflicts with Keychron's functions) 
VIA mapping works too once flashed for testing simple changes.

New idea/concept for future work: I could do the same behavior with just three layers a bunch of functions re-mapping the Macro Keys based on the global MacroID number.
Might branch and try that to see if there is any performance or bin file size improvement. 
For now, I'll keep this as it's doing what I wanted to.



## Layers
After months of use of `santacrx_layers`, I realized that I was not using the secondary qwerty layer I had.
I also noticed that the funcionalities I wanted on my knob where limited by the setup.
Lastly, I had to sometimes reconfigure my macros in VIA just so I could be producitve that day depending on what I ws going to do. 
This keymap addresses all of the above, by allowing multiple knob and macro configurations based on the software package to be used.
Its build up on using lights to indicate which state/layer we are in so that I can know where we are just by glancing at my keeb.


### Description
The following table describes the intended layer functinality.
I made the decision to have 8 layers just beacause its a clean binary number and allows for a future addition without rework.

Layer definition:

| Bit |Status|	Name   |	Keys    |	Macros	|	Knob          |	Lights	|
|:---:|:----:|---------|----------|---------|-----------    |-----------|
|  0  | --   | `_FN`   | Settings | --      |Change M Layer |Spiral|
| *1* | x02  |*`_BASE`*|*QWERTY*  |*Typing*	|*Side Scroll*  |*Regular*| 
|  2  | x06  | `_LV`   | ↑	      |Labview	| ↑	            |↑+Gold Macros|
|  3  | x0A  | `_DAT`  | ↑ 	      |Data		  | ↑	            |↑+Green Macros|
|  4  | x12  | `_VS`   | ↑ 	      |Code		  |L/R Arrow	    |↑+Purple Macros|
|  5  | x22  | `_CAD`  | ↑ 	      |Onshape	|Span/Rotate    |↑+Red Macros|
|  6  | x42  | `_NA`   | ↑	      | --	    |Music	        |↑+Pink	Macros|
|  7  | --   | `_NUM`  |NUM+MOUSE | --    	|U/D Wheel	    |Party|

### Layout
The overall layout is as follows, based on the tabulated description above (showing `_CAD` overlay active on top of `_BASE`):

```
Overlay feature layer
---------------------      bit|status
       ____________        ---+------
      /           /           |
   7 /___________/_         7 |   0
      /           /           |    
   6 /___________//         6 |   0
   5 /___________// ----->  5 |   1
   4 /___________//         4 |   0
   3 /___________//         3 |   0
   2 /___________//         2 |   0
,->1 /___________/_ ----->  1 |   1
|     /           /           |
|  0 /___________/          0 |   0
|                                 +
'--- default_layer = 1            |
     layer_state   = 0x0022 <-----'
```

### Functionality
Layers 0 and 7 will be toggled by the <kbd>FN</kbd> and <kbd>NUM</kbd> keys respectively.
Layers 1 through 6 are the default and overlays respectively.
The cycle will be <kbd>FN</kbd>: 1→0→1 , or <kbd>NUM</kbd>: 1→7→1. 
When in 0, the knob cycles the overlay.
The keys' backlighting color will change according to the selected overlay setting.
When returning from 0, the respective overlay will be activated and the macro colum reflects the respectiva layer color.

## Features and Functions

### Layer Interface backbone
* Layer 1 `_BASE` set as default in initializing function
* Debugging and console enabled
* Use of `Layer_Move()` for layers 1-6
* Use of custom function for layers 0 `_FN` and 7 `_NUM`

### Functions
* Macro layer selector:
  * CW knob =+1 layer index, CCW =-1. 
  * [Sample](https://docs.qmk.fm/feature_layers#example-keycode-to-cycle-through-layers) used as backbone, create two keys to get that up and down
  * bitwise operations for masking
  * custom functions to go to and get out of layer selection
* Lights
  * Change light setting based on which layer group we are on
  * make the Macro key's background color based on macro layer selected
  * layer selection layer color is based on macro setting (see table above)
  * going to the layer can be momentary (holding) or locked in place (shift while releasing)
  * Active modifier to the `_CAD` knob changes color to white
* Knob
  * On regular layers (All except `_FN` and `_NUM`):
    * <kbd>SHIFT</kdb> + :
      * <kbd>↺</kdb> : Vol + 
      * <kbd>↻</kdb> : Vol -
    * <kbd>CTRL</kdb> + :
      * <kbd>↺</kdb> : <kbd>PGUP</kdb> 
      * <kbd>↻</kdb> : <kbd>PGDN</kdb>

### Macros per Layer
* Function (`_FN`)
  * Knob
    * press: execute layer change, mute when shifted
    * rotation: layer selection
* Base (`_BASE`)
  * Knob
    * press: (empty)
    * rotation: Side Scrollwheel
  * Macro Keys
      | Key | Press | <kbd>SHFT+</kbd> |
      |:---:|:-----:|:-------:|
      | <kbd>M1</kbd>  | ñ | Ñ |
      | <kbd>M2</kbd>  | ° | π |
      | <kbd>M3</kbd>  | ± | § |
      | <kbd>M4</kbd>  | µ | Ω |
      | <kbd>M5</kbd>  | δ |   |
* LabVIEW (`_LV`)
  * Knob
    * press: activates <-> deactivates windows zoom
    * rotation: Side Scrollwheel
  * Macro Keys
      | Key | Press | <kbd>SHFT+</kbd> |
      |:---:|:-----:|:-------:|
      | <kbd>M1</kbd>  | While Loop | For Loop |
      | <kbd>M2</kbd>  | Case Frame | Sequence Frame |
      | <kbd>M3</kbd>  | Local Variable | Global Variable |
      | <kbd>M4</kbd>  | <kbd>CTRL+E</kbd>   |
* Excel/Data (`_DAT`)
  * Knob
    * press: (empty)
    * rotation: Side Scrollwheel
  * Macro Keys
      | Key | Press | <kbd>SHFT+</kbd> |
      |:---:|:-----:|:-------:|
      | <kbd>M1</kbd>  | Add Row | Delete Row |
      | <kbd>M2</kbd>  | Add Column | Delete Column |
* Code (`_VS`)
  * Knob:
    * press: (empty)
    * rotate: <kbd>←</kbd>/<kbd>→</kbd>
  * Macro Keys
      | Key | Press |
      |:---:|:-----:|
      | <kbd>M1</kbd>  | `../` |
      | <kbd>M2</kbd>  | run `cmd` + go to repo dir |
      | <kbd>M3</kbd>  | <kbd>CTRL+SHFT+P</kbd> |
* CAD/OnShape (`_CAD`)
  * Knob
    * press: changes up/down <-> right/left at knob
    * rotate: up/down or right/left
  * Macro Keys
      | Key | Press | Description |
      |:---:|:-----:|-------------|
      | <kbd>M1</kbd>  | Pan mod | Adds <kbd>LSFHT</kbd> before arrow press |
      | <kbd>M2</kbd>  | Detail Rotate mod | Adds <kbd>CTRL</kbd> before arrow press |
  
### Lights

* Added some RGB_MATRIX modes that were not turned on by default
* Global layer color effects: 
  * Transparent or unsassigned keys have no backlight. 
  * CAPS only has alphas ON
* Each layer has now a visible distinction, besides the stated above:
  * `_NUM` is visibly different than the rest with rainbow pattern.
  * `_BASE` and above, except `_NUM` 
    * share the same pattern
    * Macro column has different color based on which layer is active
    * `_CAD` changes from red to white if modifier key is active      
  * `_FN` has single color dual pinwheel with color referenced to current macro layer color

#### Showcase
* `_BASE` to `_NUM` and back:  
![NUM layer showcase](http://git.santacrx.info/assets/img/keebs/_complex_num.gif)

* `_BASE` to `_FN`, selecting macro layer with know, and then going back to `_BASE` where the macro keys are highlighted with the color  
![Macro changing color and showing in BASE](http://git.santacrx.info/assets/img/keebs/_complex_layers.gif)


## Worflow / Desired Features / Bugs
*v1.2.0* adding mod masking function to knob/encoder in working layers

*v1.1.1* added indication that the `_CAD` mods are active

*v1.1.0* added more complex macros and increasing flexibility and utility of knob using modifier keys.
The lights work on all modes, albeit there is still a bug where right after flashing I have to toggle the light setting a  while between wired and wireless mode to stick. 
~It's something to do with keychron's wireless functions.~
No, not issue persists in V10, so independent of Keychron's wireless stuff
🐛 After switching  between `_NUM` or `_FN` and `_BASE` a bunch of times since flashing, lights turn off in `_BASE` upon return. 

*v1.0.1* modding to have a similar keymap layout with my V10 max. Also, removing redundant/wrongly implemented coloring functions. 
Am considering heavily avoiding the multiple empty layers and just have more complex "keys" that will be changing behavior based on `currLayerID` and even mods.
Would like to change behavior of some macros (hell, even the knob!) when holding Shift of Caps. 
Will plan out and have that as v1.1.

*v1.0* released with the workflow below. 
All upcoming changes will be simple delta releases. 
- [x] Port over with desired layer change, test nothing broke in that port. (20240801)
  - [x] Enable Console, test output
  - [x] Disable lighting ported from `_layer`
- [x] Layer change function:
  - [x] Create supporting functions and constants (20240801)
  - [x] Test output to console, not yet perform change (20240805)
  - [x] Perform layer change (20240808)
- [x] Adapt lights to current layer setup
  - [x] Create debugging witnesses, test (20240802)
  - [x] Enable functionality (20240806)
  - [x] Make a Macro index group (20240805)
  - [x] Make Macro light function (20240805)
  - [x] Test macro light (20240812)
- [x] Create Macros (20240813)

## Sources

1. QMK docs
    1. [Cycle layer button](https://docs.qmk.fm/feature_layers#example-keycode-to-cycle-through-layers)
    2. [Indicators on progged keys](https://docs.qmk.fm/features/rgb_matrix#indicator-examples)
2. Reddit
    1. [Colors per layer](https://www.reddit.com/r/olkb/comments/e0hurb/comment/fawrcem/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button)
3. Others
    1. [Macros](https://getreuer.info/posts/keyboards/macros/index.html#process_record_user-in-depth)
    2. [Rotary by layer](https://pastebin.com/rDUzHM81)
