data = dlmread ("sol.txt");

hold off;

for i = 1:rows(data)
    row = data(i,:);

    x = row(2); y = row(3);
    s = row(1);

    dd = [x y; x + s y; x + s y + s; x y + s; x y];

    plot(dd(:,1), dd(:,2));

    hold on;
end
