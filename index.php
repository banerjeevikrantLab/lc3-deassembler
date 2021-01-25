<html>

<head>
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
</head>

<body>

    <form name="savefile" method="post" action="">
        <textarea rows="10" cols="100" name="textdata"></textarea><br/>
        <input type="submit" name="submitsave" value="Save Text to Server">
	</form>

    <br/>
    <?php
    if (isset($_POST)){
        if ($_POST['submitsave'] == "Save Text to Server") {
        
            $file = fopen("program.txt","a+");
            $text = $_POST["textdata"];
            file_put_contents("program.txt", $text);
            fclose($file);

            system('./run', $retval);

            echo '
				</pre>
				<hr />Return value: ' . $retval . '<br>';
        }
    }
    
    ?>


<script>


</script>

</body>
</html>