import flask

app = flask.Flask(__name__)
# @app.route('/<path:id>')
@app.route('/')
def test():
    id=flask.request.args.get('id')
    return flask.render_template_string(id)

if __name__ == '__main__':
    app.run()