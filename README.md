

# Memory Editor GUI Application

## This Qt-based application allows users to monitor and modify memory values of running processes on Windows.<br>
**Key features include:**

- **Process Identification**: Uses `CreateToolhelp32Snapshot` to find and identify processes by name entered via user.
- **Memory Reading**: Reads and displays memory values at specified offsets within the identified process.
- **Memory Writing**: Enables users to modify memory values and provides feedback on the success or failure of write operations.
- **GUI Theming**: Supports two themes ("dark" and "purple") selectable in ui, altering the application's appearance for user preference.
- **Error Handling**: Provides detailed error messages for failed memory operations and process identification.
- **Disabled State Styling**: Disables UI elements and applies a subdued color scheme to indicate non-functional states.

This application serves as a versatile tool for developers and enthusiasts needing to interact with and manipulate memory contents of Windows processes through a user-friendly interface.

**It comes with 2 themes-**

- Black(legacy)<br>
![gif1](https://github.com/AmoghRaina/Read-Write-Process-Memory/assets/116047470/c7eb2dc3-b651-40a1-b98e-29727f996903)

- Purple<br>
![gif2](https://github.com/AmoghRaina/Read-Write-Process-Memory/assets/116047470/bbf29274-fb45-4873-b2ef-63c2c6f5d773)


### Usage guide for this application:
**Welcome to the usage guide for this project. This guide will walk you through the features and functionality of the application.** <br>
**Prerequisites**<br>
Before starting, ensure you have the following installed:<br>
- Qt development environment (version 6.0 or higher)
- C++ compiler 
- Git (optional, for version control)

Build these files in Qt Creator <br>
Once built, open the release/debug folder and run the executable.

### Features and Functionality <br>
-   **Process Management**
    
    -   **Process Search:** Allows the user to enter the name of a process and search for it in the system.
    -   **Process Attachment:** Upon finding the specified process, the application attaches to it using its process ID .
    -   **Process ID Display:** Displays the ID of the attached process .
-   **Memory Interaction**
    
    -   **Memory Reading:** Reads the memory of the attached process at specified offsets  using `ReadProcessMemory` .
    -   **Memory Writing:** Writes data to the memory of the attached process at specified offsets using `WriteProcessMemory`.
-   **User Interface (UI)**
    
    -   **Dynamic UI Updates:** Updates UI elements based on process attachment and memory operations.
    -   **Theme Selection:** Allows the user to switch between two themes (`dark` and `purple`). Themes affect the background and styling of UI elements.
-   **Error Handling**
    
    -   **Error Display:** Displays error messages when there are issues with process attachment or memory operations.
    -   **Error Codes:** Retrieves and displays system error codes (`GetLastError()`) for detailed error reporting.
-   **User Interaction**
    
    -   **Button Actions:** Executes actions (reading, writing) when corresponding buttons are clicked.
    -   **Input Validation:** Validates user inputs for memory offsets and values before performing memory operations.
-   **Visual Customization**
    
    -   **Theme Customization:** Provides two predefined themes (`dark` and `purple`) that alter the visual appearance of the application's UI elements.
### Usage Scenarios

-   **Monitoring and Modifying Memory:**
    
    -   Users can attach to a specific process (e.g., a game or application).
    -   They can then monitor and potentially modify memory values to interact with or manipulate the behavior of the attached process.
-   **System Resource Management:**
    
    -   Allows users to manage system resources by observing memory usage and potentially altering it based on application needs.
-   **Educational and Debugging Purposes:**
    
    -   Useful for educational purposes to understand how processes and memory management work within the Windows environment.
    -   Helps in debugging applications by inspecting and modifying memory contents during runtime.

### Considerations

-   **Security and Permissions:**
    
    -   Ensure that the application runs with appropriate permissions to access and modify the memory of other processes.
    -   Consider security implications and potential system stability risks associated with modifying process memory.
