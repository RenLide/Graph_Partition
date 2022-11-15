load result.dat;
color1 = [
            0   0   0
          255   0   0
          255   0 255
           64 255   0
            0   0 255
          255 128   0
            0 191 255
] / 255;
color2 = [
          255 255 255
          255 128 128
          255 128 255
          160 255 128
          128 128 255
          255 192 128
          128 223 255
] / 255;
row = result(1,1);
column = result(1,2);
X = [-1 0 0 -1];
Y = [-1 -1 0 0];
hold on;
for i = 1 : row
    for j = 1 : column
        if result((i - 1) * column + j + 1,1) > 0
            fill(X+j, Y+i, color1(mod(result((i - 1) * column + j + 1,2), 6)+1, : ));
        else
            fill(X+j, Y+i, color2(mod(result((i - 1) * column + j + 1,2), 6)+1, : ));
        end
    end
end


