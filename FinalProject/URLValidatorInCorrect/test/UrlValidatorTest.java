

import junit.framework.TestCase;
import java.util.Random;
import org.junit.Test;
import incorrect.UrlValidator;

//import static org.junit.Assert.*;


//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!


// BUG: Schemes are set to lower case but the allowed schemes are upper case
// BUG: http works as scheme but fails @ authority -- investigate!

public class UrlValidatorTest extends TestCase {

   public UrlValidatorTest(String testName) {
      super(testName);

   }
   
   public void testManualTest() {
	   UrlValidator v = new UrlValidator();
	   
	   System.out.println(v.isValid("http://google.com"));
	   System.out.println(v.isValid("https://google.com"));
	   System.out.println(v.isValid("http://google.com?arg1=foo&arg2@bar"));
	   
	   UrlValidator v2 = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
	   System.out.println(v2.isValid("file://picture.jpg"));
	   System.out.println(v2.isValid("http://yes/this/works")); 
	   System.out.println(v2.isValid("http://www.google.com/main/subdir")); 

   }
   
   
   public void PartitionTesting()
   {

     // Partitions - 
     // Options flag - ALLOW_ALL_SCHEMES
     // Authority - google, reddit, washingtonpost, amazon, 
     // tld (top level domain) - .com, .net, .io, .xyz, .123, .\xd*#
     // protocol scheme - http, HTTP, https, HTTPS, ftp, sftp, telnet, 1234, icmp
     // port number - :1, :44, :1453, :-3, :2348920
     // path  - /main.html, /main/subdir/yes.html, /902, //main, /\main, /..main


	//Options flag partition
	UrlValidator optionFlagSet = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	UrlValidator optionFlagNotSet = new UrlValidator();

	System.out.println(optionFlagSet.isValid("http://www.google.com"));
	System.out.println(optionFlagSet.isValid("https://www.google.com"));
	System.out.println(optionFlagSet.isValid("http://www.google.com/main/subdir"));

	System.out.println(optionFlagNotSet.isValid("http://www.google.com"));
	System.out.println(optionFlagNotSet.isValid("https://www.google.com"));
	System.out.println(optionFlagNotSet.isValid("http://www.google.com/main/subdir"));

	// Authority partition
	UrlValidator authority = new UrlValidator();
	System.out.println(authority.isValid("http://www.google.com"));
	System.out.println(authority.isValid("http://www.amazon.com"));
	System.out.println(authority.isValid("http://www.reddit.com"));
	System.out.println(authority.isValid("http://www.ebay.com"));
 
	// tld
	UrlValidator tld = new UrlValidator();
	System.out.println(tld.isValid("http://www.google.com"));
	System.out.println(tld.isValid("http://www.google.net"));
	System.out.println(tld.isValid("http://www.google.io"));
	System.out.println(tld.isValid("http://www.google.123"));
	System.out.println(tld.isValid("http://www.google.*&^"));

	//Protocol scheme
	UrlValidator prot = new UrlValidator();
	System.out.println(prot.isValid("http://www.google.com"));
	System.out.println(prot.isValid("https://www.google.com"));
	System.out.println(prot.isValid("HTTP://www.google.com"));
	System.out.println(prot.isValid("HTTPS://www.google.com"));
	System.out.println(prot.isValid("ftp://www.google.com"));
	System.out.println(prot.isValid("FTP://www.google.com"));

	//Port Number
	UrlValidator portNum = new UrlValidator();
	System.out.println(portNum.isValid("http://www.google.com:80"));
	System.out.println(portNum.isValid("http://www.google.com:-3"));
	System.out.println(portNum.isValid("http://www.google.com:54056846832"));

	//Path
	UrlValidator path = new UrlValidator();
	System.out.println(path.isValid("http://www.google.com/main"));
	System.out.println(path.isValid("http://www.google.com/main/subdir"));
	System.out.println(path.isValid("http://www.google.com//main"));
	System.out.println(path.isValid("http://www.google.com/~main/subdir"));


  }
   
  

 
   public void testIsValid()
   {
	   //You can use this function for programming based testing

	Random rand = new Random();
	UrlValidator urlVal = new UrlValidator();
	UrlValidator urlVal2 = new UrlValidator(UrlValidator.ALLOW_ALL_SCHEMES);
		
	String[] protocols = {"http://", "HTTP://", "https://", "HTTPS://", "telnet://", "ssl://", "ssh://", "ssn://", "ftp://"};
	String[] domains = { "google", "apple", "reddit"};
	String[] tlds = {".com",".net",".super", ".html", ".44", ".-()*^*&", ".^^", ".io", ".co"};
	String[] paths = {"/somepath", "/main/subdir", "/~main", "", "/apple.php", "/septermber/octerber/novermber", "\\/","/99"  };
	String[] ports = {":80",":443",":-8",":186587384", "", "", ""};

		
		int i, rand1, rand2, rand3, rand4, rand5, rand6;
		
		for( i = 0; i < 100; i++) {
		
			rand1 = rand(1); //Random on flags	
			rand2 = rand(8); //protocols	
			rand3 = rand(2); // domains	
			rand4 = rand(8); //tlds	
			rand5 = rand(7); // paths	
			rand6 = rand(6); // ports	
	
			//Create a URL to test
			String passedUrl = protocols[rand2] + domains[rand3] + tlds[rand4] + ports[rand5] + paths[rand6];
		
			// Runs with Allow_all_schemes flag if true
			boolean rez
			if(rand1) {
				rez = urlVal2.isValid(passedUrl);
			} else {
				rez = urlVal.isValid(passedUrl);
			}	
		
			//Print to user test and result			
			System.out.println("Testing: " + passedUrl + ", Result: " + rez);
			
		}
		
		



   }
   


}
