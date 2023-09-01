#ifndef STD_TYPES_H
#define STD_TYPES_H

typedef unsigned char                    u8 ;
typedef unsigned short int               u16 ;
typedef unsigned long int                u32 ;
typedef unsigned long long int           u64 ;

typedef signed char                     s8 ;
typedef signed short int                s16 ;
typedef signed long int                 s32 ;
typedef signed long long int            s64 ;

typedef   float                         f32;
typedef   double                        f64 ;

#define NULL_PTR 		((void*)  0 )

typedef enum
{
	STD_TYPES_OK,STD_TYPES_NOK
}ErrorState;


#endif
