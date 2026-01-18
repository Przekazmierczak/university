function [L] = Lucas(n)
    n = n - 1;
    L = [];

    if n == -1
        return
    end

    prev = 2;
    L = [L prev];

    if n == 0
        return
    end

    curr = 1;
    L = [L curr];
    if n == 0
        return
    end
    
    for i = 2:n
        temp = curr;
        curr = curr + prev;
        prev = temp;
        L = [L curr];
    end
end