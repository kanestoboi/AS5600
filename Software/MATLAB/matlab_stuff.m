s = serial('/dev/cu.usbmodem4403201', 'BaudRate', 9600);

data(1) = 0;
data(1) = 0;

fopen(s);
tic
for i = 1:6000
    data(i) = fscanf(s,'%f');
    %filteredLoadCellData(i) = 0.00345*realLoadCellData(i) + .9966*filteredLoadCellData(i-1);
end
toc
fclose(s);

%%
Fs = 1000;
T = 1/Fs;
L = 1500;             % Length of signal
t = (0:L-1)*T;        % Time vector

x = 4*cos(2*pi*100*t);



T = 0.011;
Fs = 1/T;
L = length(velocityData1000);
t = (0:L-1)*T;        % Time vector
x = velocityData1000;

Y = fft(x);

P2 = abs(Y/L);
P1 = P2(1:L/2+1);
P1(2:end-1) = 2*P1(2:end-1);

f = Fs*(0:(L/2))/L;
plot(f,P1) 
title('Single-Sided Amplitude Spectrum of X(t)')
xlabel('f (Hz)')
ylabel('|P1(f)|')


%% Scales Discrete Filter

Fc = .05;  %filter cut off frequency
w = 2*pi*Fc;
s = tf('s');
filter  = w/(s+w);
filter = c2d(filter, 0.011)


