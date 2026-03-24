# MP3 Tag Reader

Author
Your Name:Karthik Kumar S
Date:20-03-2026


## Overview
MP3 Tag Reader is a command-line application written in C that reads and displays metadata information from MP3 files. The program parses ID3 tags and shows details such as Title, Artist, Album, Year, and Album Art information.

## Features
- Reads ID3v2.3 metadata
- Fallback support for ID3v1 tags
- Displays Title, Artist, Album, Year
- Detects Album Art (APIC frame)
- Command-line Help Menu (-h)
- Safe frame parsing and error handling
- Modular code structure


## Build Instructions

make

-- Run Program

./mp3_reader tests/sample.mp3

-- Help Menu

./mp3_reader -h