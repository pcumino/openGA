% DATA = load("-ascii", "../myBin/main-result.txt");
% DATA
filename = "../myBin/main-result.txt";
delim = "	";

DATA = importdata(filename, delim, 1);
x = DATA.data(:,[2]);
y = DATA.data(:,[3]);
cost1 = DATA.data(:,[4]);
cost2 = DATA.data(:,[5]);
meancost = (cost1+cost2)/2;

t = -10:0.1:10;
% eval1 = ((t+2).^2) - 10;
eval1 = (-(t+2).^2) - 10;
eval2 = ((t-2).^2) + 20;

figure('Units','normalized','Position',[0 0 1 1])
subplot(2,1,1)
for n = 1:(length(x)-1)
	plot(x(n), -((x(n)+2).^2) - 10, 'o', 'MarkerSize', 12); hold on; grid on;
	plot(y(n), ((y(n)-2).^2) + 20, 'o', 'MarkerSize', 12); hold on; grid on;
end

plot(t, eval1, 'r'); hold on; grid on;
plot(t, eval2, 'r'); hold on; grid on;

subplot(2,1,2)
plot(cost1, 'r', 'LineWidth', 2); hold on; grid on;
plot(cost2, 'b', 'LineWidth', 2); hold on; grid on;
plot(meancost, 'g', 'LineWidth', 2); hold on; grid on;


pause();