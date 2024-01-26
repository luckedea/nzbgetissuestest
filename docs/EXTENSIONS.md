## NZBGet Extensions

The core functionality of NZBGet can be extended using extension scripts. NZBGet provides documented entry points for scripts. On certain events the scripts are executed, they receive information about event, do certain work and can communicate with NZBGet to give it instructions for further processing.

## Installation

### Manualy
Option ScriptDir defines the location of extension scripts. To make a script available in NZBGet put the script into this directory. Then go to settings tab in web-interface (if you were already on settings tab switch to downloads tab and then back to settings tab to reread the list of available scripts from the disk).

Menu at the left of page should list all extension scripts found in ScriptDir. Select a script to review or change its options (if it has any).

### Using Extension Manager
In NZBGet v23, was introduced the Extension manager available in the SETTINGS tab, which can be used to automatically downloading/updating/installing extensions supported by the nzbget development team.

## Writing extension 
NZBGet Extensions can be of two versions:

## V1 (Legacy) - Not recommended
Based on configuration definition, e.g.:

    #!/bin/sh 

    ###########################################
    ### NZBGET POST-PROCESSING SCRIPT       ###

    # Print test message.
    #
    # This is a test script. It prints one message to log. Here in the
    # long description we could write instructions for user.
    #
    # The long description can have multiple paragraphs when needed. Like
    # this one.

    ### NZBGET POST-PROCESSING SCRIPT       ###
    ###########################################

If you need to create an Extension V1 then follow this [Extension V1 (Legacy) Documentation](EXTENSIONS-LEGACY.md).

## V2 (NZBGet v23 and above) - Recommended
Based on manifest.json

## Configuration definition

Each extension must have a manifest.json file:

```json
    {
        "main": "main.py",
        "name": "Logger",
        "homepage": "",
        "kind": "POST-PROCESSING",
        "displayName": "Logger",
        "version": "2.0.0",
        "author": "Andrey Prygunkov",
        "license": "GNU",
        "about": "Logger",
        "queueEvents": "",
        "requirements": [
            "This script requires Python to be installed on your system."
        ],
        "description": [
            "This script saves the download and post-processing log of nzb-file",
            "into file _nzblog.txt in the destination directory."
        ],
        "options": [],
        "commands": [],
        "taskTime": ""
    }
```
All attributes are required!


## What is considered an extension

NZBGet scans all files and directories in script-directory (option ScriptDir) and all files in first-level sub-directories looking for manifest.json. If a it is found, the directory with manifest.json is considered to be an extension.


Example:

    ppscripts                                <directory with pp-scripts, option ScriptDir>

    ppscripts\MyCoolScript                   <directory for your cool extension>
    ppscripts\MyCoolScript\MyCoolScript.py   <your extension>
    ppscripts\MyCoolScript\manifest.json     <meta-data describing the extension>
    ppscripts\MyCoolScript\Util.py           <module required for your extension>
    ppscripts\MyCoolScript\DB.py             <module required for your extension>

## Configuration options

Let’s say we are writing a script to send E-Mail notification. The user needs to configure the script with options such as SMTP-Server host, port, login and password. To avoid hard-coding of these data in the script NZBGet allows the script to define the required options in the configuration section. The options are then made available on the settings page for user to configure.

Every option belongs to a configuration section. In the next example we define a new section with two options:

    ################################
    ### OPTIONS                  ###

    # SMTP server host.
    #Server=smtp.gmail.com

    # SMTP server port (1-65535).
    #Port=25

If your script have a lot of options you can define more than one section but you should try to avoid this. Splitting your script into several scripts may be a better alternative.

When the user saves settings in web-interface the script configuration options are saved to NZBGet configuration file using the script name as prefix. For example:

    EMail.py:Server=smtp.gmail.com
    EMail.py:Port=25

When the script is executed NZBGet passes the values of all configuration options to the script using environment variables. This will be described later in this document.

Since NZBGet automatically adds script name when saving the options, the options defined in different scripts are not interfere with each other or with NZBGets own options. It’s not necessary to add a prefix to option names.

## Bad:

    # SMTP server host.
    #EMailServer=smtp.gmail.com

    # SMTP server port (1-65535).
    #EMailPort=25

## Good:

    # SMTP server host.
    #Server=smtp.gmail.com

    # SMTP server port (1-65535).
    #Port=25

Notice the options EMailServer and EMailPort renamed to Server and Port.

## Script context
NZBGet passes different information to the script. All data is passed as environment variables (env-vars).

## NZBGet configuration options

All NZBGet configuration options are passed using env-vars with prefix NZBOP_. The variable names are written in UPPER CASE. For Example option ParRepair is passed as environment variable NZBOP_PARREPAIR. The dots in option names are replaced with underscores, for example NZBOP_SERVER1_HOST. For options with predefined possible values (yes/no, etc.) the values are passed always in lower case.

## Example: test if option “Unpack” is active

    if [ "$NZBOP_UNPACK" != "yes" ]; then
    echo "[ERROR] Please enable option \"Unpack\" in nzbget configuration file"
    fi

## Script configuration options

Script configuration options (script-options) are passed using env-vars with prefix NZBPO_. There are two env-vars for each option:

- one env-var with the name exactly as defined by pp-option;
- another env-var with the name written in UPPER CASE and with special characters replaced with underscores.

For example, for pp-option Server.Name two env-vars are passed: NZBPO_Server.Name and NZBPO_SERVER_NAME.

NOTE: In a case the user has installed the script but have not saved the configuration, the options are not saved to configuration file yet. The script will not get the options passed. This is a situation your script must handle. You can either use a default settings or terminate the script with a proper message asking the user to check and save configuration in web-interface. Example (python):

    required_options = ('NZBPO_FROM', 'NZBPO_TO', 'NZBPO_SERVER', 'NZBPO_PORT', 'NZBPO_ENCRYPTION',

    'NZBPO_USERNAME', 'NZBPO_PASSWORD', 'NZBPO_FILELIST', 'NZBPO_BROKENLOG', 'NZBPO_POSTPROCESSLOG')

    for optname in required_options:

    if (not optname in os.environ):

        print('[ERROR] Option %s is missing in configuration file. Please check script settings' % optname[6:])
        sys.exit(POSTPROCESS_ERROR)


## Custom commands

Sometimes it may be helpful to be able to execute extension scripts from settings page. For example pp-script EMail.py could use a button “Send test email”. For other scripts something like “Validate settings” or “Cleanup database” may be useful too.

Starting from v19 it is possible to put buttons on the script settings page. The buttons are defined as part of script configuration, similar to script configuration options but with a slightly different syntax:

    # To check connection parameters click the button.
    #ConnectionTest@Send Test E-Mail

This example creates a button with text “Send Test E-Mail” and description “To check connection parameters click the button.”.

The line defining button name and caption should not contain equal character (=). Otherwise it would appear as an usual option with edit field.

Older NZBGet versions (prior v19) ignore command definitions. Therefore scripts utilizing the new feature can be also used in older NZBGet version without breaking it.

When user presses the button NZBGet executes the script in a special context passing button name via env. var NZBCP_COMMAND. The script can check if it runs in command mode by examining this variable (python example):

    # Exit codes used by NZBGet

    COMMAND_SUCCESS=93
    COMMAND_ERROR=94

    # Check if the script is executed from settings page with a custom command
    command = os.environ.get('NZBCP_COMMAND')
    test_mode = command == 'ConnectionTest'
    if command != None and not test_mode:
    print('[ERROR] Invalid command ' + command)
    sys.exit(COMMAND_ERROR)

    if test_mode:
    print('[INFO] Test connection...')
    sys.exit(COMMAND_SUCCESS)

    <script continues in normal mode>

During execution of the script NZBGet presents a special dialog showing script output. The script must exit with one of predefined exit codes indicating success (exit code 93) or failure (exit code 94).

User may close the progress dialog but the script continues running in the background. All messages printed by the script are saved to NZBGet log and are seen in web-interface on Messages tab.

See post-processing script EMail.py for the reference implementation.

## Tips

NZBGet version is passed in env-var NZBOP_VERSION. Example values:

- for stable version: nzbget-11.0;
- for testing version: nzbget-11.0-testing-r620

NZBGetVersion=os.environ['NZBOP_VERSION']

    if NZBGetVersion[0:5] < '11.1':
    print('[ERROR] This script requires NZBGet 11.1 or newer. Please update NZBGet')
    sys.exit(POSTPROCESS_ERROR)

## Script consisting of multiple files

If your script consists or multiple files, put the script and all related files into a subdirectory within ppscripts-directory. NZBGet scans the first-level subdirectory of ppscripts-directory and will find your main script file (the file containing script definition signature). All other files will be ignored. You can also created subdirectories in your script-directory. These subdirectories will not be scanned.

Example:

    ppscripts                                <directory with pp-scripts, option ScriptDir>
    ppscripts\EMail.py                       <E-Mail script supplied with NZBGet>
    ppscripts\MyCoolScript                   <directory for your cool script>
    ppscripts\MyCoolScript\MyCoolScript.py   <your cool script>
    ppscripts\MyCoolScript\Util.py           <module required for your script>
    ppscripts\MyCoolScript\DB.py             <module required for your script>

TIP: if you have many files it’s better to put them in a separate subdirectory. In this case the files will not be scanned by NZBGet and the web-interface might load a little bit faster. Example:

    ppscripts                                <directory with pp-scripts, option ScriptDir>
    ppscripts\MyCoolScript                   <directory for your cool script>
    ppscripts\MyCoolScript\MyCoolScript.py   <your cool script>
    ppscripts\MyCoolScript\lib               <directory with modules required for your cool script>
    ppscripts\MyCoolScript\lib\Util.py       <module required for your script>
    ppscripts\MyCoolScript\lib\DB.py         <module required for your script>
