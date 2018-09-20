function angle = stepper(position)

persistent icount a

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
    
% setup encoder variable for I2C communication
encoder = i2cdev(a, '36');

write(encoder, hex2dec('0C'), 'uint8');
msb = read(encoder, 1, 'uint8');
write(encoder, hex2dec('0D'), 'uint8');
lsb = read(encoder, 1, 'uint8');

msb = bitand(15,msb);                      % do bit mask of 0b00001111
msb = double(bitshift(int16(msb), 8));    % shift 4 MSBs to left
angle = msb + lsb;

% move stepper extra steps

end