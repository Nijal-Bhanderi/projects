function convertCode() {
    let code = document.getElementById("codeInput").value;
    let lines = code.split("\n");
    let pseudo = [];

    for (let line of lines) {
        line = line.trim();

        // Handle if-statements
        if (line.match(/^if\s*\(.*\)/)) {
            pseudo.push("IF condition THEN");
        }
        // Handle else-if
        else if (line.match(/^else if\s*\(.*\)/)) {
            pseudo.push("ELSE IF condition THEN");
        }
        // Handle else
        else if (line.match(/^else\s*{/)) {
            pseudo.push("ELSE");
        }
        // Handle for loops
        else if (line.match(/^for\s*\(.*\)/)) {
            pseudo.push("FOR each item in range DO");
        }
        // Handle while loops
        else if (line.match(/^while\s*\(.*\)/)) {
            pseudo.push("WHILE condition DO");
        }
        // Handle function declarations
        else if (line.match(/^(int|void|float|double|string)\s+\w+\s*\(.*\)/)) {
            pseudo.push("DEFINE function");
        }
        // Handle return
        else if (line.match(/^return\s+/)) {
            pseudo.push("RETURN value");
        }
        // Handle print
        else if (line.match(/(cout|printf|console\.log)/)) {
            pseudo.push("DISPLAY output");
        }
        // Skip opening/closing braces
        else if (line === "{" || line === "}") {
            continue;
        }
        // Default
        else {
            pseudo.push("DO: " + line);
        }
    }

    document.getElementById("pseudoOutput").value = pseudo.join("\n");
}
