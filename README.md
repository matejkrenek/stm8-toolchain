<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->
<a name="readme-top"></a>
<!--
*** Thanks for checking out the Best-README-Template. If you have a suggestion
*** that would make this better, please fork the repo and create a pull request
*** or simply open an issue with the tag "enhancement".
*** Don't forget to give the project a star!
*** Thanks again! Now go create something AMAZING! :D
-->

<div align="center">
  <h2 align="center">STM8 Toolchain</h2>

  <p align="center">
    Easy to use toolchain for building applications with STM8
    <br />
    <a href="https://github.com/matejkrenek/stm8-toolchain/issues">Report Bug</a>
    ·
    <a href="https://github.com/matejkreenk/stm8-toolchain/issues">Request Feature</a>
  </p>
</div>

<br/>

<!-- TABLE OF CONTENTS -->
### Table of contents
  <li>
    <a href="#about-the-toolchain">About The Toolchain</a>
  </li>
  <li>
    <a href="#getting-started">Getting Started</a>
    <ul>
      <li><a href="#prerequisites">Prerequisites</a></li>
      <li><a href="#installation">Installation</a></li>
    </ul>
  </li>
  <li><a href="#usage">Usage</a></li>
  <li><a href="#contact">Contact</a></li>
  <li><a href="#acknowledgments">Acknowledgments</a></li>



<!-- ABOUT THE TOOLCHAIN -->
## About The Toolchain

This toolchain is based on compilation with SDCC and programming the controller with STVP. This allows you to use all the features of C99 standard and use any programmer that is supported by STVP.

In addition to this, unused functions are removed during compilation with the use of sdccrm.

<!-- GETTING STARTED -->
## Getting Started

Follow all the steps below for desired functionality of the toolchain.

Disclaimer: the steps are described for windows because i suppose linux users are much smarter than windows users so they don't need to be guided XD

### Prerequisites

Before running the toolchain on your machine, some necessary tools need to be downloaded.

You may have some of these tools already downloaded.

#### Nodejs
- Toolchain use nodejs to handle more complex tasks (parsing json config, calculating the size of files, adjusting SPL library)
- Download (download the LTS version): [nodejs.org](https://nodejs.org/en/)
#### STVP
- Programmer to flash the program to stm
- STVP comes with STVD that is distributed by STM. There are some license stuffs so to be sure everything is working properly follow these guides: [www.elektromys.eu](http://www.elektromys.eu/clanky/stm8_2_stvd/clanek.html)
#### SDCC
- Compiler to compile the program
- Download: [sdcc.sourceforge.net](https://sdcc.sourceforge.net/)
#### Others
   ```sh
   choco install git make vscode mingw
   ```
### Installation

Now when all necessary tools are downloaded you can run the toolchain on your machine. 

1. Clone the repo

   ```sh
   git clone https://github.com/matejkrenek/stm8-toolchain.git {project_name}
   ```
2. Edit config.json according to you needs

   ```json
   {
      "device": "STM8S103",
      "flash": {
          "stvp_path": "C:/Program Files (x86)/STMicroelectronics/st_toolset/stvp/",
          "stlink": "ST-LINK",
          "device": "STM8S103F3"
      }
   }
   ```
   #### Supported parameters
    | Property        | Values                            |
    | --------------- | --------------------------------- |
    | "device"        | STM8S103, STM8S105, STM8S208      |
    | "flash.stlink"  | Any programmer supported by STVP  |
    | "flash.device"  | Any device supported by STVP      |
    
3. After editing config.json 

   ```sh
   make update
   ```

<!-- USAGE EXAMPLES -->
## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<!-- CONTACT -->
## Contact

Matěj Křenek - [mate23.krenek@gmail.com](mailto:mate23.krenek@gmail.com)

Project Link: [https://github.com/matejkrenek/stm8-toolchain](https://github.com/matejkrenek/stm8-toolchain)


<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Apart from this toolchain I recommend any of these:
* [Wykys stm8 tools](https://gitlab.com/wykys/stm8-tools)
* [Marrek Nozka](https://github.com/spseol/STM8-deroboard-start)

<p align="right">(<a href="#readme-top">Back to top</a>)</p>
