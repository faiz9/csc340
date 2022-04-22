package com.company;
import java.util.*;

//enum will store the search keyword, part of speech, and definition.
//removed public because it was giving me run errors.
//create constructors use getters to return value.

enum search {
    Arrow("Arrow", "noun", "Here is one arrow: <IMG> -=>> </IMG>"),
    Book1("Book", "noun", "A set of pages."),
    Book2("Book", "noun", "A written work published in printed or electronic form."),
    Book3("Book", "verb", "To arrange for someone to have a seat on a plane."),
    Book4("Book", "verb", "To arrange something on a particular date."),
    Distinct1("Distinct", "adjective", "Familiar. Worked in Java."),
    Distinct2("Distinct", "adjective", "Unique. No duplicates. Clearly different or of a different kind."),
    Distinct3("Distinct", "adverb", "Uniquely. Written 'distinctly'."),
    Distinct4("Distinct", "noun", "A keyword in this assignment."),
    Distinct5("Distinct", "noun", "An advanced search option."),
    Distinct6("Distinct", "noun", "Distinct is a parameter in this assignment."),
    Placeholder1("Placeholder", "adjective", "To be updated..."),
    Placeholder2("Placeholder", "adverb", "To be updated..."),
    Placeholder3("Placeholder", "conjunction", "To be updated..."),
    Placeholder4("Placeholder", "interjection", "To be updated..."),
    Placeholder5("Placeholder", "noun", "To be updated..."),
    Placeholder6("Placeholder", "preposition", "To be updated..."),
    Placeholder7("Placeholder", "pronoun", "To be updated..."),
    Placeholder8("Placeholder", "verb", "To be updated..."),
    Reverse1("Reverse", "adjective", "On back side."),
    Reverse2("Reverse", "adjective", "Opposite to usual or previous arrangement."),
    Reverse3("Reverse", "noun", "A dictionary program's parameter."),
    Reverse4("Reverse", "noun", "Change to opposite direction."),
    Reverse5("Reverse", "noun", "The opposite."),
    Reverse6("Reverse", "noun", "To be updated..."),
    Reverse7("Reverse", "noun", "To be updated..."),
    Reverse8("Reverse", "noun", "To be updated..."),
    Reverse9("Reverse", "noun", "To be updated..."),
    Reverse10("Reverse", "verb", "Change something to opposite."),
    Reverse11("Reverse", "verb", "Go back."),
    Reverse12("Reverse", "verb", "Revoke ruling."),
    Reverse13("Reverse", "verb", "To be updated..."),
    Reverse14("Reverse", "verb", "To be updated..."),
    Reverse15("Reverse", "verb", "Turn something inside out.");
//    ReverseOK1("ReverseOK1", "ok", "is NOT a part of speech"),
//    ReverseOK2("ReverseOK2", "ok", "is NOT 'distinct' "),
//    ReverseOK3("ReverseOK3", "ok", "is NOT 'reverse' "),
//    ReverseOK4("ReverseOK4", "ok", "was disregarded ");
    //ReverseOK5("ReverseOK5","ok","is NOT 'distinct' "),


    private String keyword;
    private String speech;
    private String definition;

    private search(String keyword, String speech, String definition) {
        this.keyword = keyword;
        this.speech = speech;
        this.definition = definition;
    }

    //getters and return

    public String getKeyword() {
        return this.keyword.toLowerCase(); //if user inputs using lower case
    }

    public String getSpeech() {
        return this.speech;
    }

    public String getDefinition() {
        return this.definition;
    }

    @Override
    public String toString() {
        return this.keyword + " [" + this.speech + "]: " + this.definition;
    }


    //reverse
    public static ArrayList<search> reverse(ArrayList<search> search) {
        for (int i = 0; i < search.size() / 2; i++) {
            search temp = search.get(i);
            search.set(i, search.get(search.size() - i - 1));
            search.set(search.size() - i - 1, temp);
        }
        return search;
    }


    //stores same elements of speech
    public static ArrayList<search> sameSpeech(ArrayList<search> search, String speech) {
        ArrayList<search> list = new ArrayList<search>();
        if (search != null) {
            for (search entry : search) {
                String Speech = entry.getSpeech(); //had to make S in speech uppercase to remove error
                if (speech.equalsIgnoreCase(speech)) {
                    list.add(entry);
                }
            }
        }
        return list;
    }


    //Distinct; removes duplicates
    public static ArrayList<search> distinctSearch(ArrayList<search> search) {
        HashMap<String, search> hmap = new HashMap<String, search>();

        for (search entry : search) {
            String definition = entry.getDefinition();
            if (!hmap.containsKey(definition)) {
                hmap.put(definition, entry);
            }
        }
        ArrayList<search> sortSearch = new ArrayList<search>(hmap.values());
        if (!hmap.toString().equalsIgnoreCase("reverse")) {
            Collections.sort(sortSearch);
        }

        return sortSearch;
    }

//enum
    public static void main(String[] args) {
        String[] keyword = {"Arrow","Book","Distinct","Placeholder","Reverse","Noun","Verb","Adjective","Conjunction","Interjection","Preposition","OK","facebook"}; //,"ReverseOK"};
        System.out.println("! Loading data...");


        //error for the keyword
        HashMap<String, ArrayList<search>> map = new HashMap<String, ArrayList<search>>();

        for (search entry: search.values()) {
            String Keyword = entry.getKeyword();

            ArrayList<search> speechdef;

            if (map.containsKey(keyword)) {
                speechdef = map.get(keyword);
            } else {
                speechdef = new ArrayList<search>();
            }
            speechdef.add(entry);
            map.put(Keyword, speechdef);
        };

        System.out.println("! Loading complete...");
        System.out.println("\n===== DICTIONARY 340 JAVA =====");

        System.out.println("----- Keywords: " + keyword.length);
        System.out.println("----- Definitions: " + search.values().length + "\n");

        boolean run = true;
        int counter = 0;

        while (run) {
            counter++;
            Boolean distinct = false;
            Boolean reverse = false;
            System.out.print("Search [" + counter + "]: ");
            Scanner input = new Scanner(System.in);
            String userSearch = input.nextLine();
            String speech = null;
            String searchName = null;

            String[] parameter = userSearch.split(" ");
            String[] totalSpeech = {"noun", "verb", "adjective", "adverb", "pronoun", "preposition", "conjunction", "interjection"};

            if (parameter.length > 0) {
                searchName = parameter[0];
            }

            if (parameter.length > 1 && parameter[1] != null) {
                if (Arrays.asList(totalSpeech).contains(parameter[1].toLowerCase())) {
                    speech = parameter[1];
                } else if (parameter[1].toLowerCase().equalsIgnoreCase("distinct")) {
                    distinct = true;
                } else if (parameter[1].toLowerCase().equalsIgnoreCase("reverse")) {
                    reverse = true;
                }  else {
                    System.out.println("     |");
                    System.out.println("     <The entered 2nd parameter '" + parameter[1] + "' is NOT a part of speech.>" );
                    System.out.println("     <The entered 2nd parameter '" + parameter[1] + "' is NOT 'distinct'.>");
                    System.out.println("     <The entered 2nd parameter '" + parameter[1] + "' is NOT 'reverse'.>");
                    System.out.println("     <The entered 2nd parameter '" + parameter[1]+ "' was disregarded.>");
                    System.out.println("     <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>");
                   // System.out.println("     |");
                }
            }
            if(parameter.length > 2 && parameter[2]!=null) {
                if ((Arrays.asList(totalSpeech).contains(parameter[2].toLowerCase()))) {
                    speech = parameter[2];
                } else if (parameter[2].toLowerCase().equalsIgnoreCase("distinct")) {
                    distinct = true;
                } else if (parameter[2].toLowerCase().equalsIgnoreCase("reverse")) {
                    reverse = true;
                }  else {
                    System.out.println("     |");
                    System.out.println("     <The entered 3rd parameter '" + parameter[2] + "' is NOT a part of speech.>" );
                    System.out.println("     <The entered 3rd parameter '" + parameter[2] + "' is NOT 'distinct'.>");
                    System.out.println("     <The entered 3rd parameter '" + parameter[2] + "' is NOT 'reverse'.>");
                    System.out.println("     <The entered 3rd parameter '" + parameter[2] + "' was disregarded.>");
                    System.out.println("     <The 3rd parameter should be a part of speech or 'distinct' or 'reverse'.>");
                   // System.out.println("     |");
                }
            }
            if(parameter.length > 3 && parameter[3]!=null) {
                if (parameter[3].toLowerCase().equalsIgnoreCase("reverse")) {
                    reverse = true;
                }  else {
                    System.out.println("     |");
                    System.out.println("     <The entered 4th parameter '" + parameter[3] + "' is NOT a part of speech.>" );
                    System.out.println("     <The entered 4th parameter '" + parameter[3] + "' is NOT 'reverse'.>");
                    System.out.println("     <The entered 4th parameter '" + parameter[3] + "' was disregarded.>");
                    System.out.println("     <The 4th parameter should be a part of speech or 'distinct' or 'reverse'.>");
                  //  System.out.println("     |");
                }
            }
            if (!userSearch.equalsIgnoreCase("!q")) {
                System.out.println("     |");
                ArrayList<search> pKeyword = map.get(searchName.toLowerCase());
                ArrayList<search> pDistinct = (distinct) ? distinctSearch(pKeyword) : pKeyword;
                ArrayList<search> pSpeech = (speech != null) ? sameSpeech(pDistinct, speech) : pDistinct;
                ArrayList<search> rKeyword = (reverse) ?  reverse(pKeyword): pKeyword;
                ArrayList<search> reverseDistinct = (reverse) ? reverse(pDistinct): pDistinct;
                ArrayList<search> rSpeech = (reverse) ? reverse(pSpeech): pSpeech;
                if (pSpeech != null && pSpeech.size() > 0) {
                    for(search entry: pSpeech) {
                        System.out.print("      " + entry + "\n");
                    }
                } else {
                    System.out.println("     <NOT FOUND> To be considered for the next release. Thank you.");
                    System.out.println("     |");
                    System.out.println("      PARAMETER HOW-TO, please enter:");
                    System.out.println("      1. A search key - then 2. An optional part of speech -then");
                    System.out.println("      3. An optional 'distinct' - then 4. An optional 'reverse'");
                    System.out.println("     |");
                }
                System.out.println("     |");
            } else {
                System.out.println(" -----THANK YOU-----");
                break;
            }
        }

    }

}
