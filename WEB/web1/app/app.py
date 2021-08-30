# -*- coding: utf-8 -*-
from flask import Flask,redirect, url_for, escape, request,Response
import base64
from werkzeug.utils import secure_filename
import os
app = Flask(__name__)
app.config['UPLOAD_FOLDER'] =os.getcwd()
app.config['MAX_CONTENT_LENGTH'] = 100 * 1024
ALLOWED_EXTENSIONS = set(['zip'])

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS


@app.route('/', methods=['POST','GET'])
def hello():
    return '''
    <!doctype html>
    <title>Upload new File</title>
    <h1>Upload new File</h1>
    <form method=post action="http://0.0.0.0:8080/upload" enctype=multipart/form-data>
      <input type=file name=file>
      <input type=submit value=Upload>
    </form>
    '''

@app.route('/upload',methods=['POST','GET'])
def upload_file():
    file = request.files['file']
    if file.filename == '':
        return "文件名为空？"
    if file and allowed_file(file.filename):
        filename = secure_filename(file.filename)
        file_save_path = os.path.join(app.config['UPLOAD_FOLDER'], filename)
       # return file_save_path
        if(os.path.exists(file_save_path)):
            return 'This file already exists'
        file.save(file_save_path)
    else:
        return 'This file is not a zipfile'


    try:
        extract_path = file_save_path + '_'
        os.system('unzip -n ' + file_save_path + ' -d '+ extract_path)
        read_obj = os.popen('cat ' + extract_path + '/*')
        file = read_obj.read()
        read_obj.close()
        os.system('rm -rf ' + extract_path)
    except Exception as e:
        file = None

    os.remove(file_save_path)
    if(file != None):
        if(file.find(base64.b64decode('aGN0Zg==').decode('utf-8')) != -1):
            return 'error'
    return Response(file)

@app.route('/flag')
def find_flag():
    return error


if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True, port=8080)



