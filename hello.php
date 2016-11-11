<?php

    $size=0;
    
    $table =[];
    
    function size()
    {
        global $size;
        return $size;
    }
    
    function load($dictionary)
    {
        $lines = file(dictionary);
        
        foreach($lines as $line)
        {
            $table[$line] = true;
        }
    }
    
    function check($word)
    {
        if($table[$word] == true)
        {
            return true;
        }
        
        else
        {
            return false;
        }
    }
    
    function unload()
    {
        return;
    }
    

?>