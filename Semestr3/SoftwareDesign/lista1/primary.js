const isPrimary = (n) => {  
    for (let i = 2; i < n; i++) {
        if (n % i === 0) {
            return false; 
        }
    }
    return true;
};

let res = [];
for(let i = 2; i <= 100000; i++) {
    if (isPrimary(i)) {
        res.push(i);
    }
}

console.log(res);
