N = 15;
x1 = 1:length(theta1);
x2 = 1:length(theta2);
p1_coeffs = polyfit(x1,theta1,N);
p2_coeffs = polyfit(x2,theta2,N);

y1 = zeros(1,length(x1));
for i = 1:N+1
    y1 = y1 + p1_coeffs(i).*x1.^(N+1-i);
end

y2 = zeros(1,length(x2));
for i = 1:N+1
    y2 = y2 + p2_coeffs(i).*x2.^(N+1-i);
end

tiledlayout(2,1);
nexttile;
plot(x1,y1,x1,theta1)
nexttile;
plot(x2,y2,x2,theta2)

y1 = y1';
y2 = y2';