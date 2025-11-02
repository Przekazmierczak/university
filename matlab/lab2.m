% %Zadanie 2
% zad2x1 = linspace(-5, 5,  21);
% zad2x2 = linspace(-3, 6, 46);
% 
% zad2f = @(x) sin(x);
% zad2g = @(x) round(x);
% 
% subplot(1, 2, 1);
% plot(zad2x1, zad2f(zad2x1), 'r');
% xlabel('x'),ylabel('y');
% legend('sin(x)');
% subplot(1,2,2);
% plot(zad2x2, zad2g(zad2x2), 'b');
% xlabel('x'),ylabel('y');
% legend('round(x)');
% 
% %Zadanie 3
% zad3x = linspace(-5, 5, 100);
% 
% zad3f1 = @(x) sin(x);
% zad3f2 = @(x) cos(x);
% zad3f3 = @(x) tan(x);
% zad3f4 = @(x) abs(x);
% zad3f5 = @(x) x;
% 
% subplot(2,3,1);
% plot(zad3x, zad3f1(zad3x), 'b');
% 
% subplot(2,3,2);
% plot(zad3x, zad3f2(zad3x), 'g');
% 
% subplot(2,3,4);
% plot(zad3x, zad3f3(zad3x), 'k');
% 
% subplot(2,3,5);
% plot(zad3x, zad3f4(zad3x), 'r');
% 
% subplot(2,3,6);
% plot(zad3x, zad3f5(zad3x), 'm');
% 
% %Zadanie 4
% zad4x1 = linspace(-4, 6, 101);
% zad4x2 = linspace(2, 4, 201);
% 
% zad4f1 = @(x) sin(x) + 0.2*rand();
% 
% axes('Position', [0 0 0.8 0.8]);
% plot(zad4x1, zad4f1(zad4x1));
% axes('Position', [0.6 0.6 0.4 0.4]);
% plot(zad4x2, zad4f1(zad4x2));

% %Zadanie5
% [X,Y] = meshgrid(-10:0.1:10,-5:0.1:5);
% Z = X.^2 + Y.^2;
% mesh(X, Y, Z);
% hold on
% plot3(0,0,0, 'ro');

%Zadanie6
[X, Y] = meshgrid(200:500, 200:500);
Z = 418.9829*2-X.*sin(sqrt(abs(X)))-Y.*sin(sqrt(abs(Y)));
contour(X,Y,Z, 'ShowText','on');

%Zadanie7
xp = [200, 300, 425, 420];
yp = [200, 225, 300, 420];
hold on
plot(xp, yp, '-o');
plot(xp(1), yp(1), 'ro');
plot(xp(4), yp(4), 'r^');
hold off