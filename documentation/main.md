# Documentation

> Before following instructions, please ensure you have downloaded DevKitPro on your machine.\
> DevKitPro can be found [here](https://devkitpro.org/wiki/Getting_Started).

## Execution

1. In the root directory of the repository, use the command ```make```
2. In the root directory of the repository, a ```.nds``` file will appear
3. Launch the ```.nds``` file with your choice of emulator in file explorer
    > DeSmuME is recommended; you can download it [here](https://desmume.org/download/)

    ### Optional execution settings
    
    For those wishing to launch the ```.nds``` file via VSCode without needing to navigate the file explorer, follow the instructions below.

    1. Being by creating a VSCode Task by pressing ```Ctrl + Shift + P``` on Windows or ```Cmd + Shift + P``` on MacOS.
    2. Search for and select ```Tasks: Configure Task```.
    3. Configure ```tasks.json``` with the following:
        ```
        {
        "version": "2.0.0",
        "tasks": [
            {
                "label": "open NDS files",
                "type": "shell",
                "command": "C:\\Path\\To\\emulator.exe",  // IMPORTANT: Replace with your emulator's path
                "args": [
                    "${file}"
                ],
                "group": {
                    "kind": "build",
                    "isDefault": true
                },
                "problemMatcher": []
            }
        ]
        }
        ```
        > Ensure you have correctly pasted the path to your emulator's execution file or you will receive errors
    4. Complete steps 1 & 2 of the non-optional section (using the ```make``` command in the root) before proceeding.
    5. In VSCode, select the ```.nds``` file.
    6. Press ```Ctrl + Shift + B``` on Windows or ```Cmd + Shift + B``` on MacOS to trigger the default build task.
