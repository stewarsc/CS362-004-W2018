

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   //runs isValid() method and compares result to expected
   public void manualHelper(String url, UrlValidator urlVal, boolean expected)
   {
	   boolean result = urlVal.isValid(url);
	   System.out.printf("URL: '%s', Expected: %b, Result: %b; ", url, expected, result);
	   
	   if (expected == result) System.out.println("TEST PASSED!");
	   else System.out.println("TEST FAILED!");
   }
   
   //manually tests isValid()
   //tests by changing the part of the URL tested
   public void testManualTest()
   {	   
	   System.out.println("\n******** Manual Testing ********");
	   
	   boolean expected = true;
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
	   //checking different schemes
	   expected = true;
	   manualHelper("http://www.google.com", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://www.googlecom", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http:/www.google.com", urlVal, expected);
	   
	   //causes failure and will exit program
	   expected = true;
	   //manualHelper("ftp://www.google.com", urlVal, expected);
	   
	   //causes crashing when running
	   expected = true;
	   //manualHelper("h3t://www.google.com", urlVal, expected);
	   
	   //testing different authorities
	   expected = true;
	   manualHelper("http://go.com", urlVal, expected);
	   
	   expected = true;
	   manualHelper("http://0.0.0.0", urlVal, expected);
	   
	   expected = true;
	   manualHelper("http://255.255.255.255", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://256.256.256.256", urlVal, expected);
	   
	   expected = true;
	   manualHelper("http://255.com", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://", urlVal, expected);
	   
	   //doesn't allow empty authority with file, but does with http
	   expected = true;
	   //manualHelper("file://", urlVal, expected);
	   
	   //testing URL ports
	   expected = true;
	   manualHelper("http://www.google.com:80", urlVal, expected);
	   
	   expected = true;
	   manualHelper("http://www.google.com:65535", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://www.google.com:65636", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://www.google.com:-1", urlVal, expected);
	   
	   //testing URL paths
	   expected = true;
	   manualHelper("http://www.google.com/firstPath", urlVal, expected);
	   
	   expected = true;
	   manualHelper("http://www.google.com/$23h", urlVal, expected);
	   
	   expected = true;
	   manualHelper("http://www.google.com/test1/file", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://www.google.com/../", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://www.google.com/..//file", urlVal, expected);
	   
	   //checking URL query
	   expected = true;
	   manualHelper("http://www.google.com?action=view", urlVal, expected);
	   
	   expected = true;
	   manualHelper("http://www.google.com?action=edit&mode=up", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://www.google.com!action=view", urlVal, expected);
	   
	   expected = false;
	   manualHelper("http://", urlVal, expected);
   }
   
   
 //Test for the schemes
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing
       
	   System.out.println("Input Partitioning Test: URL Schemes");
	   
	   
       //URL validator
       UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
       
       //Valid test cases
       String[]  checkAccept = {"http://"};
       
       //Invalid test cases
       String[] checkReject = {"http:/", "http::", ":://", ":/", "23://"};
       
       //Counter for test count and loop
       int count = 0;
       int i = 0;
       
       //Get the total length and internal length
       int totalLength = checkAccept.length + checkReject.length;
       int innerLen = 0;
       int outerLen = 0;
       
       //Count for test passed and failed
       int testPassed = 0;
       int testFailed = 0;
       
       //Loop to check for test cases
       for(i = 0; i < totalLength; i++){
           
           //Valid test cases
           if (outerLen < checkAccept.length){
               
               //Check the url string
               String[] stringURL = {"" + checkAccept[outerLen] + "www.oregonstate.edu"};
           
               
               //Valid test should pass
               if(urlVal.isValid(stringURL[0])){
                   
                   //For passed test cases
                   testPassed = testPassed + 1;
               }
           
               //If the test failed
               else{
                   
                   //For failed test cases
                   System.out.println("Test Failed for URL (Incorrect Reject) : " + stringURL[0]);
                   testFailed = testFailed + 1;
               }
               
                //Counter for accept test cases
               	outerLen = outerLen + 1;
            }
           
            //Invalid test cases
            else{
                
                //Check the url string
                String[] stringURL = {"" + checkReject[innerLen] + "www.oregonstate.edu"};
                
                //Invalid test should fail
                if(urlVal.isValid(stringURL[0])){
                    
                    //For failed test
                    System.out.println("Test Failed for URL (Incorrect Accept): " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //If the test passed
                else{
                    
                    //For test passed
                    testPassed = testPassed + 1;
                
                }

                //Counter for reject test cases
                innerLen = innerLen + 1;
           }
           
           //Counter for total tests
           count = count + 1;
       }
       
       //Print out for test results
       System.out.println("Total Test: " + count);
       System.out.println("Passed Test: " + testPassed);
       System.out.println("Failed Test: " + testFailed);
   }
   

    //Test for authority
    public void testYourSecondPartition(){
        
        //You can use this function to implement your Second Partition testing
        
    		System.out.println("Input Partitioning Test: URL Authority");
    	
        //URL validator
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //Valid test cases
        String[]  checkAccept = {"google.com", "255.255.255.255", "oregonstate.edu", "0.0.0.0", "yahoo.in"};
        
        //Invalid test cases
        String[] checkReject = {"", "192.168.256.256", "0.0.0.-255", ".in"};
        
        //Counter for test count and loop
        int count = 0;
        int i = 0;
        
        //Get the total length and internal length
        int totalLength = checkAccept.length + checkReject.length;
        int innerLen = 0;
        int outerLen = 0;
        
        //Count for test passed and failed
        int testPassed = 0;
        int testFailed = 0;
        
        //Loop to check for test cases
        for(i = 0; i < totalLength; i++){
            
            //Valid test cases
            if (outerLen < checkAccept.length){
                
                //Check the url string
                String[] stringURL = {"http://" + checkAccept[outerLen] + ""};
                
                
                //Valid test should pass
                if(urlVal.isValid(stringURL[0])){
                    
                    //For passed test cases
                    testPassed = testPassed + 1;
                }
                
                //If the test failed
                else{
                    
                    //For failed test cases
                    System.out.println("Test Failed for URL (Incorrect Reject) : " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //Counter for accept test cases
                outerLen = outerLen + 1;
            }
            
            //Invalid test cases
            else{
                
                //Check the url string
                String[] stringURL = {"http://" + checkReject[innerLen] + ""};
                
                //Invalid test should fail
                if(urlVal.isValid(stringURL[0])){
                    
                    //For failed test
                    System.out.println("Test Failed for URL (Incorrect Accept): " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //If the test passed
                else{
                    
                    //For test passed
                    testPassed = testPassed + 1;
                    
                }
                
                //Counter for reject test cases
                innerLen = innerLen + 1;
            }
            
            //Counter for total tests
            count = count + 1;
        }
        
        //Print out for test results
        System.out.println("Total Test: " + count);
        System.out.println("Passed Test: " + testPassed);
        System.out.println("Failed Test: " + testFailed);
    }
    //You need to create more test cases for your Partitions if you need to
    
    //Test for port
    public void testYourThirdPartition(){
        
        //You can use this function to implement your Second Partition testing
        
    		System.out.println("Input Partitioning Test: URL Port");
    	
        //URL validator
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //Valid test cases
        String[]  checkAccept = {":", ":80", ":0", ":1234", ":10000"};
        
        //Invalid test cases
        String[] checkReject = {":-80", ":a8", ":88a", ":ki", ":10-8"};
        
        //Counter for test count and loop
        int count = 0;
        int i = 0;
        
        //Get the total length and internal length
        int totalLength = checkAccept.length + checkReject.length;
        int innerLen = 0;
        int outerLen = 0;
        
        //Count for test passed and failed
        int testPassed = 0;
        int testFailed = 0;
        
        //Loop to check for test cases
        for(i = 0; i < totalLength; i++){
            
            //Valid test cases
            if (outerLen < checkAccept.length){
                
                //Check the url string
                String[] stringURL = {"http://www.oregonstate.edu" + checkAccept[outerLen] + ""};
                
                
                //Valid test should pass
                if(urlVal.isValid(stringURL[0])){
                    
                    //For passed test cases
                    testPassed = testPassed + 1;
                }
                
                //If the test failed
                else{
                    
                    //For failed test cases
                    System.out.println("Test Failed for URL (Incorrect Reject) : " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //Counter for accept test cases
                outerLen = outerLen + 1;
            }
            
            //Invalid test cases
            else{
                
                //Check the url string
                String[] stringURL = {"http://www.oregonstate.edu" + checkReject[innerLen] + ""};
                
                //Invalid test should fail
                if(urlVal.isValid(stringURL[0])){
                    
                    //For failed test
                    System.out.println("Test Failed for URL (Incorrect Accept): " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //If the test passed
                else{
                    
                    //For test passed
                    testPassed = testPassed + 1;
                    
                }
                
                //Counter for reject test cases
                innerLen = innerLen + 1;
            }
            
            //Counter for total tests
            count = count + 1;
        }
        
        //Print out for test results
        System.out.println("Total Test: " + count);
        System.out.println("Passed Test: " + testPassed);
        System.out.println("Failed Test: " + testFailed);
    }
    
    //Test for path
    public void testYourFourthPartition(){
        
    		System.out.println("Input Partitioning Test: URL Path");
    	
        //URL validator
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //Valid test cases
        String[]  checkAccept = {"/file", "/232", "/file8", "/."};
        
        //Invalid test cases
        String[] checkReject = {"/../", "//", "//check/file", "/check//file"};
        
        //Counter for test count and loop
        int count = 0;
        int i = 0;
        
        //Get the total length and internal length
        int totalLength = checkAccept.length + checkReject.length;
        int innerLen = 0;
        int outerLen = 0;
        
        //Count for test passed and failed
        int testPassed = 0;
        int testFailed = 0;
        
        //Loop to check for test cases
        for(i = 0; i < totalLength; i++){
            
            //Valid test cases
            if (outerLen < checkAccept.length){
                
                //Check the url string
                String[] stringURL = {"http://www.oregonstate.edu" + checkAccept[outerLen] + ""};
                
                
                //Valid test should pass
                if(urlVal.isValid(stringURL[0])){
                    
                    //For passed test cases
                    testPassed = testPassed + 1;
                }
                
                //If the test failed
                else{
                    
                    //For failed test cases
                    System.out.println("Test Failed for URL (Incorrect Reject) : " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //Counter for accept test cases
                outerLen = outerLen + 1;
            }
            
            //Invalid test cases
            else{
                
                //Check the url string
                String[] stringURL = {"http://www.oregonstate.edu" + checkReject[innerLen] + ""};
                
                //Invalid test should fail
                if(urlVal.isValid(stringURL[0])){
                    
                    //For failed test
                    System.out.println("Test Failed for URL (Incorrect Accept): " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //If the test passed
                else{
                    
                    //For test passed
                    testPassed = testPassed + 1;
                    
                }
                
                //Counter for reject test cases
                innerLen = innerLen + 1;
            }
            
            //Counter for total tests
            count = count + 1;
        }
        
        //Print out for test results
        System.out.println("Total Test: " + count);
        System.out.println("Passed Test: " + testPassed);
        System.out.println("Failed Test: " + testFailed);
    }
    
    //Test for query
    public void testYourFifthPartition(){
        
    		System.out.println("Input Partitioning Test: URL Query");
    		
        //URL validator
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        //Valid test cases
        String[]  checkAccept = {"?q=result", "?x=y&a=b", "?xx=y", "", "?z=z;z=z"};
        
        //Invalid test cases
        String[] checkReject = {"=result", "-q=result", "!x=x&x=a", "xys=xs&?", "x"};
        
        //Counter for test count and loop
        int count = 0;
        int i = 0;
        
        //Get the total length and internal length
        int totalLength = checkAccept.length + checkReject.length;
        int innerLen = 0;
        int outerLen = 0;
        
        //Count for test passed and failed
        int testPassed = 0;
        int testFailed = 0;
        
        //Loop to check for test cases
        for(i = 0; i < totalLength; i++){
            
            //Valid test cases
            if (outerLen < checkAccept.length){
                
                //Check the url string
                String[] stringURL = {"http://www.oregonstate.edu" + checkAccept[outerLen] + ""};
                
                
                //Valid test should pass
                if(urlVal.isValid(stringURL[0])){
                    
                    //For passed test cases
                    testPassed = testPassed + 1;
                }
                
                //If the test failed
                else{
                    
                    //For failed test cases
                    System.out.println("Test Failed for URL (Incorrect Reject) : " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //Counter for accept test cases
                outerLen = outerLen + 1;
            }
            
            //Invalid test cases
            else{
                
                //Check the url string
                String[] stringURL = {"http://www.oregonstate.edu" + checkReject[innerLen] + ""};
                
                //Invalid test should fail
                if(urlVal.isValid(stringURL[0])){
                    
                    //For failed test
                    System.out.println("Test Failed for URL (Incorrect Accept): " + stringURL[0]);
                    testFailed = testFailed + 1;
                }
                
                //If the test passed
                else{
                    
                    //For test passed
                    testPassed = testPassed + 1;
                    
                }
                
                //Counter for reject test cases
                innerLen = innerLen + 1;
            }
            
            //Counter for total tests
            count = count + 1;
        }
        
        //Print out for test results
        System.out.println("Total Test: " + count);
        System.out.println("Passed Test: " + testPassed);
        System.out.println("Failed Test: " + testFailed);
    }
   
    //programming based testing
   public void testIsValid()
   {
	   System.out.println("\n******** Programming Based Testing ********");
	   String[] schemes = {"http", "https", "ftp"};
	   UrlValidator urlVal = new UrlValidator(schemes);
	   Random random = new Random();
	   String[] scheme = {"http://", "https://", "ftp://", "pdf://"}; 	   //String array comprised of URL components
	   Boolean[] schemeExpected = {true, true, true, false}; 	   //Boolean array w/ expected values corresponds w/ URL component
	   String[] hostname = {"www.", "", "_^?."};
	   Boolean[] hostnameExpected = {true, true, false};
	   String[] domain = {"apple", "amazon", "microsoft", "google", "oregonstate", "stanford", "java", "wikipedia", "stackoverflow", "______"};
	   Boolean[] domainExpected = {true, true, true, true, true, true, true, true, true, false};
	   String[] topDomain = {".com", ".edu", ".net", ".gov", ".org", ".999"};
	   Boolean[] topDomainExpected = {true, true, true, true, true, false};
	   String[] path = {"/search", "/test2/file3", "/", "\\", ""};
	   Boolean[] pathExpected = {true, true, true, false, true};
	   
	   String[][] urlParts = {scheme, hostname, domain, topDomain, path};	//Holds array components
	   Boolean[][] urlExpected = {schemeExpected, hostnameExpected, domainExpected, topDomainExpected, pathExpected};  //Holds expected boolean values
	   
	   for (int j=0; j<50; j++) {
		   String testUrl = "";		//Reset Url string
		   Boolean expected = true;
		   //Build Url string by selecting randomly from pool of random components
		   //Each component is selected in sequence
		   for (int i=0; i<urlParts.length; i++) {
			   int n = random.nextInt(urlParts[i].length);   //Generate pseudorandom number to index urlParts array
			   testUrl += urlParts[i][n];					
			   expected = expected && urlExpected[i][n];	//Aggregate boolean logic determines overall expected value
		   }
		   boolean result = urlVal.isValid(testUrl);		//Checks if testUrl is a valid url address
		   //Testing Oracle
		   System.out.printf("URL: '%s', Expected: %b, Result: %b; ", testUrl, expected, result);
		   if (expected == result) System.out.println("TEST PASSED!");
		   else System.out.println("TEST FAILED!");		//can use System.err.println to print to standard error
	   }
   }

}
