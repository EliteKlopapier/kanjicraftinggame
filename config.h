#ifndef CONFIG_H
#define CONFIG_H

// Whether to print verbose output. Comment out to disable.
#define VERBOSE

// Path to IDS file (containing recipes). Better not change this.
#define IDS_PATH "resources/ids/IDS_content_only.TXT"

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
#define PREFERRED_VARIANT 'U'


#endif // ifndef CONFIG_H