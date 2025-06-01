const fs = require("fs")
let content = 
// `
// VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2(
//     VkDevice                                    device,
//     uint32_t                                    bindInfoCount,
//     const VkBindBufferMemoryInfo*               pBindInfos);
// `
fs.readFileSync("")


let lines = content.toString().split("\n")

let result = []

let apiStart = false

let params = []

function addAPI(){
    let head = params[0] 
    head = head.replace(" VKAPI_CALL ", ",")
    head = head.replace("(", ",(")
    head = head.replace("VKAPI_ATTR ", "YKM22_VULKAN_SYMBOL(\n")

    result.push(head);

    params[params.length - 1] = params[params.length - 1].replace(";", ",")

    let pnames = [];
    let plines = "(";

    for (let i = 1; i < params.length; i++) {
        const l = params[i].trim();
        result.push(params[i]);
        plines += l.match(/[\w]+(?=\W*$)/)[0];
        if (i < params.length - 1) {
            plines += ", ";
        }
    }

    plines += "));"
    result.push(plines);
    result.push("");
}

for (let line of lines) {
    if (apiStart){
        if (line === "" || line.startsWith("#")){
            addAPI();
            apiStart = false;
            params = [];
        }else{
            params.push(line);
        }
    }else if (line.startsWith("VKAPI_ATTR")) {
        apiStart = true;
        params.push(line);
        continue;
    }
}

result = result.join("\n");
fs.writeFileSync("vkwrap.cpp", result);

