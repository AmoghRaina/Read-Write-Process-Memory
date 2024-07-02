
# Memory Editor GUI Application

## This Qt-based application allows users to monitor and modify memory values of running processes on Windows.<br> Key features include:

- **Process Identification**: Uses `CreateToolhelp32Snapshot` to find and identify processes by name entered via a QLineEdit.
- **Memory Reading**: Reads and displays memory values at specified offsets within the identified process.
- **Memory Writing**: Enables users to modify memory values and provides feedback on the success or failure of write operations.
- **GUI Theming**: Supports two themes ("darkest" and default) selectable via QComboBox, altering the application's appearance for user preference.
- **Error Handling**: Provides detailed error messages for failed memory operations and process identification.
- **Disabled State Styling**: Disables UI elements and applies a subdued color scheme to indicate non-functional states.

This application serves as a versatile tool for developers and enthusiasts needing to interact with and manipulate memory contents of Windows processes through a user-friendly interface.

**It comes with 2 themes-**

- Black(legacy)<br>
![gif1](https://github.com/AmoghRaina/Read-Write-Process-Memory/assets/116047470/c7eb2dc3-b651-40a1-b98e-29727f996903)
<br>
- Purple-<br>
![gif2](https://github.com/AmoghRaina/Read-Write-Process-Memory/assets/116047470/bbf29274-fb45-4873-b2ef-63c2c6f5d773)

<br>
