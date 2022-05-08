a. In /profile: encode html entities contained in req.query.username
b. In views/pages/transfer/form.ejs, add a csrf_token hidden field. In router.js, use HMAC to encrypt the cookie with a randomly generated key, and then set the csfr_token value to this encrypted cookie when rendering the transfer form. In /post_transfer, require the csfr token to be as expected.
c. In /post_transfer: Check if the hashed password stored in cookie is the same as the hashed password in the database.
d. In /post_transer: First, update bitbars in the database instead of req.session.account.bitbars. Second, update cookie.
e. In /close: use parameterized sql query instead.
f. In app.js: set the content-security-policy.
g. In /get_login: Also sleep if the username and password combination does not exist.
