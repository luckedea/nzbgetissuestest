## About extension scripts

The core functionality of NZBGet can be extended using extension scripts. NZBGet provides documented entry points for scripts. On certain events the scripts are executed, they receive information about event, do certain work and can communicate with NZBGet to give it instructions for further processing.

## Using extension scripts
Option ScriptDir defines the location of extension scripts. To make a script available in NZBGet put the script into this directory. Then go to settings tab in web-interface (if you were already on settings tab switch to downloads tab and then back to settings tab to reread the list of available scripts from the disk).

Menu at the left of page should list all extension scripts found in ScriptDir. Select a script to review or change its options (if it has any).