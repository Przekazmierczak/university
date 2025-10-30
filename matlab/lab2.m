%Zadanie 1
x1 = linspace(0, 10, 100);
x2 = linspace(0, 10, 20);

f1 = @(x) 8*sin(x)-2*x;
f2 = @(x) abs(f1(x));
plot(x1, f1(x1), '-r');
hold on
plot(x2, f2(x2), 'og');
xlabel('x'), ylabel('y');
legend('8*sin(x)-2*x', '|8*sin(x)-2*x|');
hold off