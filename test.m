clc, clear, close all
feature jit off
C = input('Enter a temperature in Celsius: ');
F = (C * 1.8) + 32;
if F > 100
    fprintf('YES\n');
else
    fprintf('NO\n');
end
fprintf('Fahrenhit = %g\n', F);     % 不显示小数点后多余的0
