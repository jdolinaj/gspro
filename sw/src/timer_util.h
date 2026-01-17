// inline timer functions


void delay_ms(uint64_t ms)
{
    if (ms < 10)
    {
        uint64_t start = esp_timer_get_time();
        uint64_t end_time = start + (ms * 1000);
        
        // Handle potential overflow
        if (end_time < start) {
            // Overflow occurred, wait for wrap-around
            while (esp_timer_get_time() > start) {
                // Wait for timer to wrap
            }
        }
        
        while (esp_timer_get_time() < end_time) {
            // Busy wait
        }
    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
}

/*
void delay_ms_non_blocking(uint64_t ms)
{
    if (ms < 10)
    {
        uint64_t m = esp_timer_get_time();
        if (ms)
        {
            uint64_t e = (m + (ms * 1000));
            if (m > e)
            { // overflow
                while (esp_timer_get_time() > e)
                {
                }
            }
            while (esp_timer_get_time() < e)
            {
            }
        }
    }
    else
    {
        vTaskDelay(pdMS_TO_TICKS(ms));
    }
}
*/