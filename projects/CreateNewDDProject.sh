#! /bin/bash
echo "Give a project Name :"
read projectName
mkdir $projectName
unzip DDProject.zip -d ./$projectName

#let rename directory
find ./$projectName -type d -name '*DDProjectName*' | while read FILE ; do
    newfile="$(echo ${FILE} |sed -e 's/DDProjectName/'${projectName}'/')" ;
    mv "${FILE}" "${newfile}" ;
done 

#let rename file
find ./$projectName -type f -name '*DDProjectName*' | while read FILE ; do
    newfile="$(echo ${FILE} |sed -e 's/DDProjectName/'${projectName}'/')" ;
    mv "${FILE}" "${newfile}" ;
done 

#now replace DDProjectName by ${projectName} in files
find ./$projectName -type f ! -name '*.png' ! -name '*.ttf' | while read FILE ; do
if [[ $OSTYPE == darwin* ]]; then 
	sed -i "" 's/DDProjectName/'${projectName}'/g' "${FILE}"
else
	sed -i 's/DDProjectName/'${projectName}'/g' "${FILE}"
fi
done 