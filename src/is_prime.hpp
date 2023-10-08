#pragma once

bool isPrime(long int n)
{
    // Corner case
    if (n <= 1)
        return false;
 
    // Check from 2 to n-1
    for (long int i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return false;
 
    return true;
}