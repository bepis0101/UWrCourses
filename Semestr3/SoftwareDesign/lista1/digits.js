function isDivisbleBySumOfDigits(n) {
    let sum = 0;
    let digits = n.toString().split('');
    for (let digit of digits) {
        sum += parseInt(digit);
    }
    return n % sum === 0;
}

function isDivisibleByEveryDigit(n) {
    let digits = n.toString().split('');
    for (let digit of digits) {
        if (n % parseInt(digit) !== 0) {
            return false;
        }
    }
    return true;
}


let res = [];
for(let i = 1; i <= 100000; i++) {
    if (isDivisibleByEveryDigit(i) && isDivisbleBySumOfDigits(i)) {
        res.push(i);
    }
}


console.log(res);