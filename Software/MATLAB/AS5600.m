a = arduino('com11','Uno', 'libraries', 'I2C');

%%
addrs = scanI2CBus(a)

%%

encoder = i2cdev(a, '36');
%%
write(encoder, hex2dec('0C'), 'uint16');
msb = read(encoder, 1, 'uint16');
write(encoder, hex2dec('0D'), 'uint16');
lsb = read(encoder, 1, 'uint16');

msb = bitand(15,msb);                      % do bit mask of 0b00001111
msb = double(bitshift(int16(msb), 8));    % shift 4 MSBs to left
angle = msb + lsb
