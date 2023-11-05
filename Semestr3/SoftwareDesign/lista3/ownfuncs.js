function forEach( a, f ) {
    for( var i = 0; i < a.length; i++ ) {
        f( a[i] );
    }
}

function map( a, f ) {
    var result = [];
    for( var i = 0; i < a.length; i++ ) {
        result[i] = f( a[i] );
    }
    return result;
}
function filter( a, f ) {
    var result = [];
    for( var i = 0; i < a.length; i++ ) {
        if ( f( a[i] ) ) {
            result.push( a[i] );
        }
    }
    return result;
}

function greaterThan2( x ) {
    return x > 2;
}

forEach( [1,2,3], console.log );
console.log(map( [1,2,3], x => x*x ));
console.log(filter( [1,2,3], greaterThan2 ));
