function [res] = mirror(n)
    nString = num2str(n);
    sizeOfN = size(nString);
 
    for i = 1:floor(sizeOfN(2)/2)
        temp = nString(i);
        nString(i) = nString(sizeOfN(2) + 1 - i);
        nString(sizeOfN(2) + 1 - i) = temp;
    end
    res = str2num(nString);
end