# Tribes Vengeance Heightmap Exporter
## How to use

1. Compile the project using the x86 build configuration to produce a .dll file
2. Run Tribes Vengeance
3. Inject the .dll file into Tribes Vengeance
4. Enter a map
5. Press the INSERT key - A file named "heightmap_0.bin" should be produced in the Bin directory of your Tribes Vengeance folder (where TV_CD_DVD.exe is)
6. Place the heightmap_0.bin file in a folder with heightmap_parser.py and run heightmap_parser.py
7. An image file named "heightmap_0.png" should be created within the same folder as heightmap_parser.py

## Help
- If pressing the INSERT key does not create heightmap_0.bin try pressing CTRL + INSERT
- If pressing the INSERT key does not create heightmap_0.bin try running Tribes Vengeance as Administrator