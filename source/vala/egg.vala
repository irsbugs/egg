/**
 * Egg Timer
 * egg.vala
 * 
 * Objective: Compile in C and expose the API functions so that other languages
 * may have bindings to these functions
 * 
 * Reference:
 * http://helgo.net/simon/introspection-tutorial/stepone.xhtml
 * 
 * Ian Stewart
 * 2020-06-02
 */

class Egg : Object {

    void greeting () {
        print("\nEgg Timer - 0.1. written in Vala.\n");
    }
    
    void start_egg_timer(int duration) {
        /**
         * start_egg_timer(int duration)
         */
        // Seconds since Epoch
        int64 seconds_now = GLib.get_real_time () / 1000000;
        string time_stamp = (seconds_now.to_string());
        //print ("Time stamp: %s\n", time_stamp);
        //print ("Duration: %d\n", duration);

        string text_save = (time_stamp + "," + duration.to_string()); 
        try {
            FileUtils.set_contents ("/tmp/egg.data", text_save);
        } catch (Error e){
                stderr.printf("Error: %s", e.message);
        }
        var dt = new DateTime.now_local ();
        stdout.puts (dt.format ("\n\tEgg timer started: %e %b %Y %k:%M:%S\n"));            
        print("\tTimer set for: %d seconds\n", duration);                
    }

    void time_elapsed() {
        /**
         * time_elapsed()
         * 
         */
        try {
            string text;
            FileUtils.get_contents ("/tmp/egg.data", out text);
            //print(text);
            string[] data = text.split (",");
            //print("%s\n",data[0]);
            //print("%s\n",data[1]);

            int64 time_start = int64.parse(data[0]);
            int64 time_now = GLib.get_real_time () / 1000000;
            int64 time_diff = time_now - time_start;
            print ("\n\tTime Elapsed: %" + int64.FORMAT + "\n", time_diff);

        } catch (Error e){
                stderr.printf("Error: %s", e.message);
        }
    }
    
    void time_remaining() {
        /**
         * time_remaining()
         * 
         */
        try {
            string text;
            FileUtils.get_contents ("/tmp/egg.data", out text);
            //print(text);
            string[] data = text.split (",");
            //print("%s\n",data[0]);
            //print("%s\n",data[1]);

            int64 time_start = int64.parse(data[0]);
            int64 duration = int64.parse(data[1]);
            int64 time_now = GLib.get_real_time () / 1000000;
            int64 time_diff = time_start + duration - time_now;
            print ("\n\tTime Remaining: %" + int64.FORMAT + "\n", time_diff);

        } catch (Error e){
                stderr.printf("Error: %s", e.message);
        }
    }    

    static void main (string[] args) {
        /**
         * main
         * display menu, retrieve input, then call function.
         * Accept the timer duration from the command line as integer seconds
         */
        var egg = new Egg ();
                
        // Command line arguments:
        //print("Command line argv[0]: %s\n", args[0]);
        //print("Length of args: %d\n", args.length);
        
        egg.greeting();
        
        int input;
        bool is_looping = true;        
        while (is_looping){
            
            stdout.printf("""
            Egg Timer Menu:
                1. Start Egg Timer
                2. Time Elapsed
                3. Time Remaining
                4. Stop Egg Timer
                
                Selection: """);

            // Check for non-numeric input
            if (stdin.scanf("%d", out input) !=1){
                print("\n\tError Non-Numeric. Enter 1 to 4...\n");
                stdin.scanf("%*s");
                continue;
            }
            
            //print("Integer Entered: %d\n",input);             
            switch(input){
            
            case 1 : 
                // Start egg timer
                //stdout.printf("Integer1: %d\n",input);  
                if (args.length < 2) {
                    egg.start_egg_timer(60);
                } 
                else {
                    egg.start_egg_timer(int.parse(args[1]));
                }
                break;
                
             case 2 :
                // Time elapsed
                //stdout.printf("Integer2: %d\n",input); 
                egg.time_elapsed();
                break;
                
            case 3 :
                // Time remaining
                //stdout.printf("Integer3: %d\n",input); 
                egg.time_remaining();
                break;
                
            case 4 :
                // Stop cooking eggs
                //stdout.printf("Integer4: %d\n",input); 
                is_looping = false;
                print("\n\tBon appetit!\n");  // é
                break;
                                
            default :
                print("\n\tInvalid Integer: %d. Enter 1 to 4...\n",input); 
                break;
            }
        }
    }
}
