## Configuration definition

Each script must have a configuration definition. The definition starts with one of the possible signatures depending on the purpose of the script:

    ### NZBGET POST-PROCESSING SCRIPT
    ### NZBGET SCAN SCRIPT
    ### NZBGET QUEUE SCRIPT
    ### NZBGET SCHEDULER SCRIPT

To end the definition the same signature is used.

If the script can be used for multiple purposes the signature can be mixed, for example:

    ### NZBGET SCAN/QUEUE SCRIPT

Example of a very simple post-processing script:

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

    echo "post-processing script test"

The first part of configuration is a short description:

    # Print test message.

This line is a short description of what our pp-script does. The short description stays near the script name in the edit download dialog. This should be a short one sentence description. The long description is separated with an empty line.

## What is considered a script

NZBGet scans all files in script-directory (option ScriptDir) and all files in first-level sub-directories looking for script definition signature ### NZBGET \<PURPOSES> SCRIPT. If a signature is found, the file is considered to be a script.

NOTE: for performance reasons NZBGet scans only first 10KB of the script. Put the script definition at the beginning of the script. The script definition can be longer than 10KB but it must start within first 10KB of the script.

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