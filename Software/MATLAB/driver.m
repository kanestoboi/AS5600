function ouput = driver(input)

persistent icount a
pwmPin = 3;

if (isempty(icount))
   try
      a = arduino;
      disp(a)
   catch
      warning('Unable to connect, user input required')
      disp('For Windows:')
      disp('  Open device manager, select "Ports (COM & LPT)"')
      disp('  Look for COM port of Arduino such as COM4')
      disp('For MacOS:')
      disp('  Open terminal and type: ls /dev/*.')
      disp('  Search for /dev/tty.usbmodem* or /dev/tty.usbserial*. The port number is *.')
      disp('For Linux')
      disp('  Open terminal and type: ls /dev/tty*')
      disp('  Search for /dev/ttyUSB* or /dev/ttyACM*. The port number is *.')
      disp('')
      com_port = input('Specify port (e.g. COM4 for Windows or /dev/ttyUSB0 for Linux): ','s');
      a = arduino(com_port,'Uno');
      disp(a)
   end
   icount = 0;
end    

%% calculate the output RMS value to output
outputValue = input * 5;

%% set the PWM voltage
writePWMVoltage(a, pwmPin, outputValue);

end