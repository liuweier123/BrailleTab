#define ISR_C
#pragma vector = TIMER0_OVF_vect
    __interrupt void TOver0_isr( void )
{
    CNT++;
    if(CNT==125)
    {
        CNT = 0;
        timer[1]++;
        if(timer[1]==60)
        {
            timer[1] = 0;
            timer[0]++;
        }
        if(timer[0]==60)
        {
            timer[0] = 0;
        }
    }
}  