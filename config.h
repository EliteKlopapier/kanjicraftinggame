#ifndef CONFIG_H
#define CONFIG_H

// Whether to print verbose output. Comment out to disable.
#define VERBOSE

// Path to IDS file (containing recipes). Better not change this.
#define IDS_PATH "resources/ids/IDS_content_only.TXT"

// Path to readings file (which also contains meanings). Better not change this.
#define READINGS_PATH "resources/unihan/Unihan_Readings.txt"

/*  ~~~~ Preferred country specific variant for recipes ~~~~
            G = China
            H = Hong Kong SAR
            J = Japan
            K = ROKorea
            M = Macau SAR
            P = DPRKorea
            S = SAT
            T = TCA/Taiwan
            U = Unicode
            B = UK
            V = Vietnam
*/
#define PREFERRED_CHARACTER_VARIANT 'U'

/* ~~~~ Additional definitions ~~~~
            J = Japanese
            C = Cantonese
            N = NONE
*/
#define ADDITIONAL_DEFINITIONS 'N'


#endif // ifndef CONFIG_H