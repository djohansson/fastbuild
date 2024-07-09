// xxHash.h
//------------------------------------------------------------------------------
#pragma once

// Includes
//------------------------------------------------------------------------------
#include "Core/Env/Types.h"
#include "Core/Strings/AString.h"

#include <xxhash.h>

// xxHash
//------------------------------------------------------------------------------
class xxHash
{
public:
    inline static uint32_t  Calc32( const void * buffer, size_t len );
    inline static uint64_t  Calc64( const void * buffer, size_t len );

    inline static uint32_t  Calc32( const AString & string ) { return Calc32( string.Get(), string.GetLength() ); }
    inline static uint64_t  Calc64( const AString & string ) { return Calc64( string.Get(), string.GetLength() ); }
private:
    enum { XXHASH_SEED = 0x0 }; // arbitrarily chosen random seed
};

// xxHash3
//------------------------------------------------------------------------------
class xxHash3
{
public:
    inline static uint64_t  Calc64( const void * buffer, size_t len );

    inline static uint64_t  Calc64( const AString & string ) { return Calc64( string.Get(), string.GetLength() ); }
};

// Calc32
//------------------------------------------------------------------------------
/*static*/ uint32_t xxHash::Calc32( const void * buffer, size_t len )
{
    return XXH32( buffer, len, XXHASH_SEED );
}

// Calc64
//------------------------------------------------------------------------------
/*static*/ uint64_t xxHash::Calc64( const void * buffer, size_t len )
{
    return XXH64( buffer, len, XXHASH_SEED );
}

// Calc64 (xxHash3)
//------------------------------------------------------------------------------
/*static*/ uint64_t xxHash3::Calc64( const void * buffer, size_t len )
{
    return XXH3_64bits( buffer, len );
}

//------------------------------------------------------------------------------
