<a name="readme-top"></a>

<div align="center">
  <h2 align="center">STM8 LCD I2C LIBRARY</h2>

  <p align="center">
    Library for stm8 to work with LCD with I2C convertor
    <br />
    <a href="https://github.com/matejkrenek/stm8-lcd-i2c/issues">Report Bug</a>
    ·
    <a href="https://github.com/matejkrenek/stm8-lcd-i2c/issues">Request Feature</a>
  </p>
</div>

<br/>

<!-- TABLE OF CONTENTS -->
### Table of contents
  <li>
    <a href="#installation">Installation</a>
    <ul>
      <li><a href="#requirements">Requirements</a></li>
    </ul>
  </li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#contact">Contact</a></li>
  <li><a href="#limitations">Limitations</a></li>

<!-- INSTALLATION -->
## Installation

You can download [.zip file](/matejkrenek/stm8-lcd-i2c/archive/refs/heads/master.zip) of the library and implement lcd_i2c.h and lcd_i2c.c to you project.

Another option is to clone the repository to your project

 ```sh
 git clone https://github.com/matejkrenek/stm8-lcd-i2c.git lcd_i2c
 ```
   
### Requirements

Library uses delay functions, so you can use your own implementation of these or you can use [stm8-delay](https://github.com/matejkrenek/stm8-delay) library.

<!-- USAGE EXAMPLES -->
## Usage
 - Initializing LCD
 - parameters:
    - address - address of LCD
    - columns - number of columns
    - rows - number of rows
 ```c
 LCD_I2C_Init(0x27, 16, 2);
 ```
 - Set cursors on display
 - parameters:
    - columns - index of column (starting from 0)
    - rows - index of row (starting from 0)
 ```c
 LCD_I2C_SetCursor(0, 1);
 ```
 - Print on display
 - parameters:
    - string - string of chars to be printed
 ```c
 LCD_I2C_Print("Hello World");
 ```
 - Turn on backlight
 ```c
 LCD_I2C_Backlight();
 ```
- Turn off backlight
 ```c
 LCD_I2C_NoBacklight();
 ```
- Clear display
 ```c
 LCD_I2C_Clear();
 ```

<!-- CONTACT -->
## Contact

Matěj Křenek - [mate23.krenek@gmail.com](mailto:mate23.krenek@gmail.com)

Project Link: [https://github.com/matejkrenek/stm8-lcd-i2c](https://github.com/matejkrenek/stm8-lcd-i2c)

<!-- LIMITATIONS -->
## Limitations

- Library is tested and supported just for uP listed in the table below

  | Supported microprocessors |
  | ------------------------- |
  | STM8S208                  |
  | STM8S105                  |
  | STM8S103                  |
